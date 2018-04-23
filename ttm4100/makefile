LTX=pdflatex
FLAGS=

all: wireshark-intro.pdf web-server.pdf udp-pinger.pdf traceroute.pdf

%.pdf: %.tex
	$(LTX) $(FLAGS) $^

.PHONY:
clean:
	rm *.dvi *.aux *.fdb_latexmk *.fls *.log

.PHONY:
purge:
	rm *.dvi *.aux *.fdb_latexmk *.fls *.log *.pdf

