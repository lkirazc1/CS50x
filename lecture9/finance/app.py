import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Get user's portfolio
    portfolio = db.execute("SELECT * FROM transactions WHERE user_id = :user_id", user_id=session["user_id"])

    # Get user's cash
    cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])

    # Get user's total
    total = cash[0]["cash"]

    # Get user's total earnings
    earnings = total + sum([x["cost"] for x in portfolio])

    return render_template("index.html", portfolio=portfolio, cash=usd(cash[0]["cash"]), total=total, earnings=earnings)



@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy_stocks.html")

    symbol = request.form.get("symbol")
    shares = int(request.form.get("shares"))
    result = lookup(symbol)
    if result is None or symbol == '':
        return apology("Invalid symbol")
    if shares < 1:
        return apology("Invalid amount of shares")
    cost = result["price"]
    name = result['name']
    symbol = result['symbol']

    cash_left = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]['cash']
    if cost * shares > cash_left:
        return apology("You don't have enough money to buy that")

    db.execute("UPDATE users SET cash = (SELECT cash FROM users WHERE id=?) - ? WHERE id=?",
               session["user_id"], cost * shares, session["user_id"])

    db.execute("INSERT INTO transactions (user_id, name, symbol, cost, shares) VALUES (?, ?, ?, ?, ?)",
               session["user_id"], name, symbol, cost, shares)

    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "GET":
        return render_template("quoted.html", invalid=False)
    result = lookup(request.form.get("symbol"))
    if not result:
        return apology("That symbol does not exist")
    return render_template("quote.html", name=result["name"], price=usd(result["price"]), symbol=result["symbol"])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if username == '' or len(db.execute("SELECT username FROM users WHERE username = ?", username)):
            return apology("Username is invalid or already exists")
        if password == '' or password != confirmation:
            return apology("Passwords do not match or invalid password")

        # insert user into database
        password_hash = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, password_hash)
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/quote")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    
    if request.method == "GET":
        return render_template("sell.html")
    
    if request.form.get("shares") <= 0:
        return apology("Not enough shares to sell")
    if request.form.get("shares") > sum()
    
