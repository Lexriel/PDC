% classe pour sujets de tp et controles
%Y. Roos juin 1999
%
%
%
% Nouvelles commandes

% 1) A placer avant \begin{document}
% \formation   (defaut vide)
% \matiere     (defaut vide)
% \genre       (defaut interrogation ecrite)
% \jour        (defaut date du jour au format mois annee)
% \commentaire (defaut vide)
% \logo        vaut miage , gmi ou lmil defaut lmil

% 2) A placer n'importe ou
% \bareme 
% \avecBareme : affiche l'argument des commandes \bareme
% \sansBareme : n'affiche pas l'argument des commandes \bareme (defaut)
% \avecSolution : affiche les solutions presentes
% \sansSolution : n'affiche pas les solutions (defaut)

% Options
%
% gmi1 , gmi2 , gmi3 , miage1 , miage2 , miage3 , licence , maitrise
% une de ces options permet d'eviter a devoir utiliser 
% les commandes \logo et \formation
% 
% solution => affiche les solutions presentes
% bareme => affiche l'argument des commandes \bareme

%
% Exemple  1 :
%                 \documentclass[gmi2,solution,bareme]{controle}
%                 \matiere{Complexit\'e et Apprentissage}
%                 \genre{Contr\^ole surprise}
%                 \commentaire{Aucun document autoris\'e}
%                 \begin{document}
%
%
% Exemple  2 :
%                 \documentclass{controle}
%                 \logo{gmi}
%                 \formation{I.U.P. G.M.I. 2}
%                 \matiere{Complexit\'e et Apprentissage}
%                 \genre{Contr\^ole surprise}
%                 \jour{mercredi 15 novembre 1995}
%                 \commentaire{Aucun document autoris\'e}
%                 \begin{document}
%                 \avecSolution
%                 \avecBareme
%

% Nouveaux environnements introduits :
%
%    question : elles sont numérotées avec un prefixe de no de section
%               si il y en a
%    definition
%    exercice : meme numerotation que section
%    remarque
%    exemple : numerotation globale aux documents
%    solution : si existe doit suivre immediatement la question 


\NeedsTeXFormat{LaTeX2e} \ProvidesClass{controle}[1999/06/15]
\LoadClass{article} 

\RequirePackage{ifthen} \RequirePackage{a4wide}
\RequirePackage{verbatim} \RequirePackage{version}
\RequirePackage{epsfig}
\RequirePackage[latin1]{inputenc}

\makeatletter

% definition du haut de page
\def\ps@ctrlheadings{\let\@mkboth\markboth
  \def\@oddhead{\protect\makebox[0pt][l]{\protect\underline
      {\protect\makebox[\textwidth][l]{\sl\rightmark\hfill\rm\thepage}}}}
  \def\@oddfoot{}
  \def\@evenhead{\protect\makebox[0pt][l]{\protect\underline
      {\protect\makebox[\textwidth][l]{\rm\thepage\hfill\sl\leftmark}}}}
  \def\@evenfoot{} }

\pagestyle{ctrlheadings}

% 
\def\formation#1{\def\styforctrl{#1}} \formation{}

\def\matiere#1{\def\stymatctrl{#1}} \matiere{}

\def\genre#1{\def\stygenctrl{#1}} \genre{Interrogation \'ecrite}

\def\jour#1{\def\stydatctrl{#1}} \jour{ \ifthenelse{\month =
    1}{janvier\ }{ \ifthenelse{\month = 2}{f\'evrier\ }{
      \ifthenelse{\month = 3}{mars\ }{ \ifthenelse{\month = 4}{avril\ 
          }{ \ifthenelse{\month = 5}{mai\ }{ \ifthenelse{\month =
              6}{juin\ }{ \ifthenelse{\month = 7}{juillet\ }{
                \ifthenelse{\month = 8}{aout\ }{ \ifthenelse{\month =
                    9}{septembre\ }{ \ifthenelse{\month = 10}{octobre\ 
                      }{ \ifthenelse{\month = 11}{novembre\ }{
                        d\'ecembre\ }}}}}}}}}}}\the\year}

\def\commentaire#1{\def\stycomctrl{#1}} \commentaire{}

\def\logo#1{\def\stylogoctrl{#1}} \logo{lmil}

% initialisation du haut de page et du debut de premiere page
\AtBeginDocument{{\markright {\sl{\styforctrl\ --\ \stymatctrl\ --\ 
        \stygenctrl}} \thispagestyle{empty}
\begin{center}
    \sffamily 
      {\bfseries
        \parbox[t]{3.2cm}
          {\epsfig{file={\stylogoctrl}.eps,height=2cm}}
        \ \ \ \ \hfill {\large \styforctrl} \ \ \hfill
        \parbox[t]{2.5cm}
          {\epsfig{file=ustl.eps,height=2cm}}
        \vskip 0.4cm 
        {\huge{\stymatctrl : \stygenctrl}}
      \vskip 0.4cm} {\large
      \stycomctrl\vskip 0.4cm \stydatctrl\vskip 0.4cm}
\end{center}}}

% Definition Exercice Exemple
\newtheorem{definition}{D\'efinition}

\newenvironment{exercice}{
  {\addtocounter{section}{1}\setcounter{question}{0}\noindent \large {\bf
      \underline{Exercice \thesection~:}\ \\}}}{\ \\}

\newtheorem{exemple}{Exemple}

% Question et gestion de l'affichage des solutions et baremes
\newboolean{avecsolution} \setboolean{avecsolution}{false}
\excludeversion{solution}
\def\avecSolution{\setboolean{avecsolution}{true}
  \includeversion{solution}}
\def\sansSolution{\setboolean{avecsolution}{false}
  \excludeversion{solution}}

\newcounter{question}[section] 
\newenvironment{question}
{\stepcounter{question} \vskip 0.1cm \noindent
 \begin{em}{\bf Question \ifthenelse{\value{section} = 0} {\thequestion}
       {\thesection.\thequestion}~:}}
   {\ifthenelse{\boolean{avecsolution}} {\vskip 0.2cm \noindent
       Solution \ifthenelse{\value{section} = 0} {\thequestion}
       {\thesection.\thequestion}~:\end{em}} {\end{em}\vskip 0.1cm
\noindent}}
 
\newboolean{avecbareme} \setboolean{avecbareme}{false}
\def\avecBareme{\setboolean{avecbareme}{true}}
\def\sansBareme{\setboolean{avecbareme}{false}}
\def\bareme#1{\ifthenelse{\boolean{avecbareme}}{(#1)}{}}

\newenvironment{remarque}{{\it Remarque~:}}{\ \\}

%avant octobre ou apres octobre ?
\newcounter{un} \newcounter{deux} 
\setcounter{un}{\year}
\setcounter{deux}{\year} 
\addtocounter{deux}{1}
\ifthenelse{\month <
  10}{\addtocounter{un}{0}}{\addtocounter{deux}{3}}

\DeclareOption{solution}{\avecSolution}
\DeclareOption{bareme}{\avecBareme}
\DeclareOption{gmi1}{\logo{gmi}\formation{IUP GMI 1 --
    \theun/\thedeux}} 
\DeclareOption{gmi2}{\logo{gmi}\formation{IUP
    GMI 2 -- \theun/\thedeux}}
\DeclareOption{gmi3}{\logo{gmi}\formation{IUP GMI 3 --
    \theun/\thedeux}}
\DeclareOption{miage1}{\logo{miage}\formation{IUP MIAGE 1 --
    \theun/\thedeux}}
\DeclareOption{miage2}{\logo{miage}\formation{IUP MIAGE 2 --
    \theun/\thedeux}}
\DeclareOption{miage3}{\logo{miage}\formation{IUP MIAGE 3 --
    \theun/\thedeux}}
\DeclareOption{licence}{\logo{ustl}\formation{INFO~$301$
    -- \theun/\thedeux}}
\DeclareOption{maitrise}{\logo{lmil}\formation{Ma\^ \i trise
    d'informatique -- \theun/\thedeux}} \ProcessOptions 
    
\endinput

