#!/bin/sh

docker run -v "$(realpath .)":/data blang/latex pdflatex book.tex
