#!/usr/bin/env python3

from flask import Flask
from flask import render_template
from flask import url_for
from flask import request

app = Flask(__name__)

@app.route("/")
def hello():
    return render_template("index.html")

@app.route("/forward", methods=["post"])
def forward_to_mshared():
    data = request.get_json()
    print(data)
    return render_template("index.html")

with app.test_request_context():
    url_for("static", filename="main.js")
    url_for("static", filename="style.css")
