\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{eeleyes}[My personal latex class]

\usepackage{luatexbase}
\RequireLuaModule{eeleyes.lua}

% General document structure
\LoadClass[12pt]{report}
\usepackage[letterpaper, margin=1.5in]{geometry}
\renewcommand{\baselinestretch}{1.25}

% Font and math
\usepackage{tgschola}
\usepackage[T1]{fontenc}
\usepackage{amsmath,amsthm,thmtools}
\usepackage[scaled=1.075,nc,vvarbb]{newtxmath}
\usepackage{physics}

% Tikz + PgfPlots
\usepackage{tikz}
\usepackage{pgfplots}

% Boxes
\usepackage{tcolorbox}
\tcbuselibrary{skins}
\tcbsetforeverylayer{shield externalize}

\newtcolorbox{hookbox}[1]{
    enhanced,
    sharp corners,
    title = {#1},
    boxrule = 0pt,
    frame empty,
    colback = white,
    colframe = black,
    coltitle = black,
    borderline west = {1pt}{0pt}{black},
    overlay unbroken and last = {
        \draw[line width=1pt, black] (frame.south west) -- ++(0:0.4cm);
    },
    attach boxed title to top left={
        xshift=-4mm,
    },
    boxed title style = {
        left = 0pt,
        right = 0pt,
        frame hidden,
        colback = white,
        sharp corners,
        boxrule = 0pt,
        borderline south = {1pt}{0pt}{black}
    }
}

% Environments

\renewcommand\qedsymbol{\Diamond}

\makeatletter
\NewDocumentCommand{\addproofref}{}{
    \par\hfill 
    \edef\tmp@proofreference{\directlua{tex.print(RefMgr.to_proof_namespace(RefMgr.pop_stack()))}}
    \footnotesize\hyperref[\tmp@proofreference]{Proof}
}

\newcommand{\createTheorem}[2]{
\newcounter{@eel@counters@#1}
\setcounter{@eel@counters@#1}{1}

\NewDocumentEnvironment{#1}{o o}{
    \phantomsection
    \IfNoValueTF{##1}{
    \begin{hookbox}{\textbf{#2 \csname the@eel@counters@#1\endcsname .}}
    }{
    \begin{hookbox}{\textbf{#2.} {##1}}
    }

    \IfNoValueF{##2}{
        \label{##2}
        \directlua{RefMgr.push_stack("##2")}
        \directlua{RefMgr.add_ref("##2", "##1")}
    }
}{
        \directlua{RefMgr.pop_stack("##2")}
    \end{hookbox}
    \refstepcounter{@eel@counters@#1}
    \@afterindentfalse\@afterheading
}
}

\RenewDocumentEnvironment{proof}{o}{
\phantomsection
\par
\normalfont \topsep6\p@\@plus6\p@\relax
\trivlist\item\relax
\pushQED{\qed}
\IfNoValueTF{#1}{
\bf Proof.\normalfont
}{
\label{\directlua{tex.print(RefMgr.to_proof_namespace("#1"))}}
\bf \hyperref[#1]{Proof of \directlua{tex.print(RefMgr.search_ref("#1"))}.} \normalfont
}
}{
\popQED
\endtrivlist
}

\makeatother

\createTheorem{theorem}{Theorem}
\createTheorem{definition}{Def}
\createTheorem{corollary}{Corollary}
\createTheorem{lemma}{Lemma}

\declaretheoremstyle[
    spaceabove = 1em,
    spacebelow = 1em
]{examplestyle}

\declaretheorem[style=examplestyle]{example}

\DeclareMathOperator{\spann}{span}
\newcommand{\R}{\mathbb{R}}

% Links
\usepackage{hyperref}
\usepackage{xcolor}

\hypersetup{
    colorlinks,
    linkcolor={red!50!black},
    citecolor={blue!50!black},
    urlcolor={blue!80!black}
}
