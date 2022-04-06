#!/bin/bash
# Scrypts for fast compiling all moduls
################################################################################
g++ -o inter inter.cc scanner.cc tid.cc ident.cc lex.cc -Wall
