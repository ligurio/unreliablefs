#!/bin/sh

mandoc -Ostyle=/unreliablefs/mandoc.css -Thtml unreliablefs.1 > unreliablefs.1.html
mandoc -Ostyle=/unreliablefs/mandoc.css -Thtml unreliablefs.conf.5 > unreliablefs.conf.5.html
