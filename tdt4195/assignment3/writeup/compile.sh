#!/bin/bash

pandoc --output assignment3.pdf assignment3.rmd
pkill -HUP mupdf-x11
