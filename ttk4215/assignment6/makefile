
writeup.pdf:writeup.rmd
	pandoc --output writeup.pdf writeup.rmd
	if ! pgrep -x "mupdf-x11" > /dev/null;then mupdf writeup.pdf & disown; fi;
	pkill -HUP mupdf-x11 
