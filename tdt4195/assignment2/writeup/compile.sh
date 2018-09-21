#!/bin/sh

pandoc -o output.pdf text2.md
pkill -HUP mupdf
