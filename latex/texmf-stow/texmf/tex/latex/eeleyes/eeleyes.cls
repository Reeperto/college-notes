\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{eeleyes}[My personal latex class]

\usepackage{luatexbase}
\RequireLuaModule{eeleyes.lua}

% General document structure
\LoadClass[12pt, fleqn]{report}
\usepackage[letterpaper, margin=1.25in]{geometry}
\renewcommand{\baselinestretch}{1.25}
\usepackage{enumitem}

% Font and math
\usepackage{tgschola}
\usepackage[T1]{fontenc}
\usepackage{amsmath,amsthm,thmtools}
\usepackage{mathtools}
\usepackage[scaled=1.075,nc,vvarbb]{newtxmath}
\usepackage{physics}

\NewDocumentCommand{\N}{}{\mathbb{N}}
\NewDocumentCommand{\Q}{}{\mathbb{Q}}
\NewDocumentCommand{\R}{}{\mathbb{R}}
\DeclareMathOperator{\spann}{span}

% Tikz + PgfPlots
\usepackage{tikz}
\usepackage{pgfplots}

% Boxes
\usepackage{tcolorbox}
\tcbuselibrary{skins, breakable}
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
    \edef\tmp@proofreference{\directlua{tex.print(Mgr.label_as_proof(Mgr.peek_label()))}}
    \footnotesize\hyperref[\tmp@proofreference]{Proof}
}

\newcommand{\createTheorem}[2]{ %-----------------------------------------------

\newcounter{@eel@counters@#1}[chapter]
\expandafter\def\csname the@eel@counters@#1\endcsname {\thechapter.\arabic{@eel@counters@#1}}
\Crefname{@eel@counters@#1}{#2}{{#2}s}

\directlua{Mgr.init_env("#1")}

\newenvironment{#1}[1][]{
\refstepcounter{@eel@counters@#1}

\IfNoValueTF{##1}{
\begin{hookbox}{\textbf{#2 \csname the@eel@counters@#1\endcsname .}}
}{
\begin{hookbox}{\textbf{#2 \csname the@eel@counters@#1\endcsname .} {##1}}
}
    \phantomsection
    \def\@tmp@envname{##1}

    \edef\@currentlabel{\csname the@eel@counters@#1\endcsname}
    \edef\@currentlabelname{\@tmp@envname}
    \edef\@currentlabeltype{@eel@counters@#1}

    \let\@oldlabel\label

    \renewcommand{\label}[1]{
        \directlua{Mgr.push_label("####1")}
        \@oldlabel{####1}
    }
}{%
    % \protected@write\@auxout{}{\string\@eel@addthmentry{#1}{\@tmp@envname}{\directlua{tex.print(Mgr.peek_label())}}}
    \directlua{Mgr.pop_label()}
\end{hookbox}
\@afterindentfalse\@afterheading
}
} %-----------------------------------------------------------------------------

\RenewDocumentEnvironment{proof}{o}{
\phantomsection
\par
\normalfont \topsep6\p@\@plus6\p@\relax
\trivlist\item\relax
\pushQED{\qed}
\IfNoValueTF{#1}{
\bf Proof.\normalfont
}{
\label{\directlua{tex.print(Mgr.label_as_proof("#1"))}}
\bf \hyperref[#1]{Proof of \Cref*{#1}.} \normalfont
}
}{
\popQED
\endtrivlist
}

\makeatother

% Links
\usepackage{hyperref}
\usepackage{cleveref}
\usepackage{xcolor}

\hypersetup{
    colorlinks,
    linkcolor={red!50!black},
    citecolor={blue!50!black},
    urlcolor={blue!80!black}
}

\createTheorem{theorem}{Theorem}
\createTheorem{definition}{Def}
\createTheorem{corollary}{Corollary}
\createTheorem{lemma}{Lemma}

\makeatletter
\newcommand{\tableofdefs}{
}
\makeatother

\declaretheoremstyle[
    spaceabove = 1em,
    spacebelow = 1em
]{blankstyle}

\declaretheorem[style=blankstyle, numbered=no]{example}
\declaretheorem[style=blankstyle, numbered=no]{remark}
