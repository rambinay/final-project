# -*- coding: utf-8 -*-
"""
Created on 2076-2-5

@author: ram binay
"""

""" *** IOT based industrial automation and monitoring*** """

from flask import Flask, render_template
import requests

app = Flask(__name__)

@app.route('/')
def index():
    l = requests.get('https://api.thingspeak.com/channels/780244/fields/1/last.txt')
    lpg = float(l.text)
    hb = requests.get('https://api.thingspeak.com/channels/780244/fields/2/last.txt')
    fire = float(hb.text)

    alc = requests.get('https://api.thingspeak.com/channels/780244/fields/3/last.txt')
    alcohol = float(alc.text)

    return render_template('major.html', lpg=lpg, fire=fire,alcohol=alcohol)

if __name__ == '__main__':
    app.run(debug=True)
