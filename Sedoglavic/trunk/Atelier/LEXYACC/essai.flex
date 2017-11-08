%{
#include <stdio.h>
#include "y.tab.h"
%}

%%
[a-zA-Z][a-zA-Z0-9]*		return WORD;
\/\*				return COMMENTSTART;
[ \t]+			        {}
\n				return NEWLINE;
\*\/				return COMMENTSTOP;
%%

