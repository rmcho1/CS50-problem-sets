import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    rows=db.execute("SELECT* FROM transactions WHERE user_id=:user_id", user_id=session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])[0]["cash"]
    
    holdings=db.execute("SELECT holdings FROM transactions WHERE user_id=:user_id", user_id=session["user_id"])

    #total amount from holdings
    total_sum= []

    for row in rows:
        symbol = str(row["symbol"])
        shares = int(row["shares"])
        name = lookup(symbol)["name"]
        price= lookup(symbol)["price"]
        total = shares * price
        row["name"] = name
        row["price"] = usd(price)
        row["total"] = usd(total)
        total_sum.append(float(total))
        
    total_cash = sum(total_sum) + cash
    
    return render_template("index.html", rows=rows, cash=cash, total_cash=total_cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        
        quote = lookup(request.form.get("symbol"))
        shares = int(request.form.get("shares"))

        # Check to see if quote exists
        if quote is None:
            return apology("Invalid symbol", 400)
        
        #Check if share quantity is above 0    
        if shares is None or shares <= 0:
            return apology("Enter valid number of shares", 400)
        
        #Lookup price of stock
        price = quote["price"]
        purchase = shares*price
        
        #name of stock
        name = quote["name"]
        
        #Check how much cash user has and if user has enough money to buy the stock
        cash = db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])
        
        if cash[0]["cash"] < purchase:
            return apology("Not enough cash to purchase this quantity of shares", 400)
        
        #Purchase stock and deduct amount from cash flow
        db.execute("UPDATE users SET cash = cash-:purchase WHERE id = :id", purchase=purchase, id = session["user_id"])
        username = db.execute("SELECT username FROM users WHERE id = :id", id = session["user_id"])
            
        #In portfolio table, add the stock information that the user bought
        # HELP!! no information was added in. I think I'm pluggin ID and username wrong
        db.execute("INSERT INTO transactions (symbol, shares, price, user_id, holdings, name) VALUES (:symbol, :shares, :price, :user_id, :holdings, :name)",
                    symbol=request.form.get("symbol"), shares=shares, price=price, user_id = session["user_id"], holdings=purchase, name=name)
        
        
        return redirect("/")
        
    else:
        return render_template("buy.html")


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

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
    if request.method == "POST":

        # Look up current stock price from API (lookup func in helpers.py)
        quote = lookup(request.form.get("symbol"))

        # Check to see if quote exists
        if quote is None:
            return apology("Invalid symbol", 400)
        
        return render_template("quoted.html", quote=quote, name=quote["name"], symbol=quote["symbol"], price=quote["price"])

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        
        #get username
        if not request.form.get("username"):
            return apology("Must provide username", 400)
            
        # get password
        elif not request.form.get("password"):
            return apology("Must provide password", 400)
            
        # confirm password
        elif not request.form.get("confirmation"):
            return apology("Must confirm password", 400)
            
        # check is password matches confirmation 
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords must match", 400)
            
        # hash the password
        password = generate_password_hash(request.form.get("password"))


        result = db.execute("INSERT INTO users (username, hash) VALUES(:username, :password)",
        username = request.form.get("username"), password = password)

        # check for database execute failure
        if not result:
            return apology("username already exists", 400)

        # log in
        session["user_id"] = result

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("register.html")
        


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        return redirect("/")
    
    else:    
        symbols=db.execute("SELECT symbol FROM transactions WHERE user_id=:user_id", user_id=session["user_id"])
        return render_template("sell.html", symbols=symbols)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
