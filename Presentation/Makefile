# usage: make filename.pdf
%.pdf: %.tex
	pdflatex $<
	biber prezentace
	pdflatex $<

clean:
	-rm *.aux *.log *.nav *.out *.snm *.toc *.bcf *.bcl *.run.xml *.bbl
