# -*- coding: utf-8 -*-
"""
Created on 7076

@author: ram binay
"""

""" *** IOT based industrial automation and monitoring*** """

from flask import Flask, render_template
import requests

app = Flask(__name__)

@app.route('/')
def index():
    t = requests.get('https://api.thingspeak.com/channels/780244/fields/1/last.txt')
    tempr = float(t.text)
    hb = requests.get('https://api.thingspeak.com/channels/780244/fields/2/last.txt')
    fire = int(hb.text)
    l = requests.get('https://api.thingspeak.com/channels/780244/fields/1/last.txt')
    lpg = int(l.text)
    h = requests.get('https://api.thingspeak.com/channels/780244/fields/1/last.txt')
    humr = float(h.text)
    return render_template('major.html', tempr=tempr, fire=fire, lpg=lpg, humr=humr)

if __name__ == '__main__':
    app.run(debug=True)
