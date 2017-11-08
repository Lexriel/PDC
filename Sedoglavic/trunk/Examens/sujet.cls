%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% classe de document latex2e pour sujets de tp, ds, td
% J.F. Roos Novembre 1995
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Les options de la classe sujet :
%  td, ds, ou tp
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Les commandes :
%  \formation
%  \matiere
%  \numerosujet
%  \auteur
%  \commentaire
%  \titresujet
%  \datesujet
%  commandes avec l'option ds uniquement :
%  \duree
%  \documents  (autorises ou pas)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{sujet}
[1995/10/15 Classe de document sujet de TP, TD, DS (JF Roos)]

% base sur la classe article
\LoadClass{article}

% packages a4 et french charges
\RequirePackage{a4wide}
\RequirePackage[greek,french]{babel}

\DeclareOption{td}{
  \newcommand{\SujetClsType}{Sujet de TD}
  \def\SujetClsDuree{}
  \def\SujetClsDocuments{}
}

\DeclareOption{tp}{
  \newcommand{\SujetClsType}{Sujet de TP}
  \def\SujetClsDuree{}
  \def\SujetClsDocuments{}
}

\DeclareOption{ds}{
  \newcommand{\SujetClsType}{Sujet d'examen}
  \newcommand{\duree}[1]{
    \def\SujetClsDuree{Dur{\'e}e #1}
  }
  \duree{2h}
  \newcommand{\documents}[1]{
    \def\SujetClsDocuments{Documents #1}
  }
  \documents{autoris{\'e}s.}
}

\DeclareOption{interro}{
  \newcommand{\SujetClsType}{Interrogation}
  \newcommand{\duree}[1]{
    \def\SujetClsDuree{Dur{\'e}e #1}
  }
  \duree{2h}
  \newcommand{\documents}[1]{
    \def\SujetClsDocuments{Documents #1}
  }
  \documents{non autoris{\'e}s.}
}

\DeclareOption*{
  \PassOptionsToClass{\CurrentOption}{article}
}

\ProcessOptions

% definition de l'entete pour les pages autres que la premiere :
%  place en header le contenu de \headtp

\def\ps@tpheadings{\let\@mkboth\markboth
  \let\@oddfoot\@empty\let\@evenfoot\@empty
  \def\@evenhead{\underline{
    \makebox[\linewidth]{\thepage\hfill\slshape\leftmark}}}
  \def\@oddhead{\underline{
    \makebox[\linewidth]{{\slshape\rightmark}\hfill\thepage}}}
  \markright{\slshape{\headtp}}
}


% header donnant: la formation, la matiere et le numero de TP
\newcommand{\headtp}{\SujetClsFormation\hfill\SujetClsType\
  \SujetClsNumero\ \SujetClsMatiere}


% definition de l'entete pour la premiere page:
%  duree et documents autorises ou pas
\def\ps@firstdsheadings{\let\@mkboth\markboth
  \let\@oddfoot\@empty\let\@evenfoot\@empty
  \def\@evenhead{\makebox[\linewidth]{\SujetClsDuree\hfill\SujetClsDocuments}}
  \def\@oddhead{\makebox[\linewidth]{\SujetClsDuree\hfill\SujetClsDocuments}}
  \markright{\slshape{\headtp}}
  }

% permet de definir la formation
\newcommand{\formation}[1]{
  \def\SujetClsFormation{#1}
  \renewcommand{\headtp}{\SujetClsFormation\hfill\SujetClsType\
  \SujetClsNumero\ \SujetClsMatiere}
  \markright{\slshape{\headtp}}
}
\def\SujetClsFormation{MIAGE}

% permet de definir la matiere
\newcommand{\matiere}[1]{
  \def\SujetClsMatiere{#1}
  \renewcommand{\headtp}{\SujetClsFormation\hfill\SujetClsType\
  \SujetClsNumero\ \SujetClsMatiere}
  \markright{\slshape{\headtp}}
}
\def\SujetClsMatiere{C}

% permet de definir le numero de TP
\newcommand{\numerosujet}[1]{
  \def\SujetClsNumero{#1}
  \renewcommand{\headtp}{\SujetClsFormation\hfill\SujetClsType\
  \SujetClsNumero\ \SujetClsMatiere}
  \markright{\slshape{\headtp}}
}
\def\SujetClsNumero{1}

% permet de definir un commentaire juste en dessous 
% du titre
\newcommand{\commentaire}[1]{
  \def\SujetClsCommentaire{#1}
}
\def\SujetClsCommentaire{}


% permet de definir la date du sujet
\newcommand{\datesujet}[1]{
  \def\SujetClsDate{#1}
}
\def\SujetClsDate{\today}

\pagestyle{tpheadings}

% permet de definir l'auteur du TP
\newcommand{\auteur}[1]{
  \def\SujetClsAuteur{\textsc{#1}}
}
\auteur{J.F. Roos}

% definition du titre du sujet
\newcommand{\titresujet}[1]{
  \title{\normalsize{\SujetClsType\ \SujetClsNumero\ \SujetClsMatiere\
    \SujetClsFormation}\\ \Large{\textbf{#1}}}
  \author{\SujetClsAuteur}
  \date{\SujetClsDate\\\small{\textsl{\SujetClsCommentaire}}}
  \maketitle
  \thispagestyle{firstdsheadings}
}

\newenvironment{sujetitemize}
{\addtolength{\parskip}{-0.2cm}
  \begin{itemize}\addtolength{\itemsep}{-0.2cm}
      \addtolength{\partopsep}{-0.2cm}}{\end{itemize}}


\newenvironment{sujetdescription}
{\addtolength{\parskip}{-0.2cm}
  \begin{description}\addtolength{\itemsep}{-0.2cm}
      \addtolength{\partopsep}{-0.2cm}}{\end{description}}