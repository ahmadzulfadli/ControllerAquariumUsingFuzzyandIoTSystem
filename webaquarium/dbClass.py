'''
http://localhost:8000/add/data?mode=save&temp=32&ph_meter=6.5
'''

from flask_sqlalchemy import SQLAlchemy
from flask import Flask, render_template, redirect, url_for, request, flash, jsonify

# objek flask
app = Flask(__name__)

# api-key
app.secret_key = "djfljdfljfnkjsfhjfshjkfjfjfhjdhfdjhdfu"

# koneksi ke database
userpass = "mysql+pymysql://fadli:Kucinghitam123"
basedir = "@127.0.0.1"
dbname = "/iot_aquarium"

app.config["SQLALCHEMY_DATABASE_URI"] = userpass + basedir + dbname
app.config["SQLALCHEMY_TRACK_MODIFICATIONS"] = False

db = SQLAlchemy(app)


class Aquarium(db.Model):
    __tablename__ = "aquarium"
    id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    data_temp = db.Column(db.Float)
    data_ph = db.Column(db.Float)
    timestamps = db.Column(db.TIMESTAMP, nullable=False,server_default=db.func.current_timestamp())

    def __init__(self, data_temp, data_ph):
        self.data_temp = data_temp
        self.data_ph = data_ph