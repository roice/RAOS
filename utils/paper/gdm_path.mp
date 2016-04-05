% figure illustrating the predefined path of gas distribution mapping

input boxes
prologues:=3;
outputtemplate:="%j.eps";

verbatimtex
%&latex
\documentclass[12pt]{article}
\begin{document}
etex

beginfig(1);

%unit
u := 1.2cm;

% edge of the arena
draw (0u, 0u) -- (10u, 0u) -- (10u, 10u) -- (0u, 10u) -- (0u, 0u) withcolor black withpen pencircle scaled 2pt;

% draw predefined path
for i = 0 upto 8:
    draw (9.5u-i*u, 9.5u) -- (9.5u-i*u, 0.5u) dashed evenly withcolor black withpen pencircle scaled 1pt;
endfor;
drawarrow (0.5u, 0.5u) -- (0.5u, 9.5u) dashed evenly withcolor black withpen pencircle scaled 1pt;
for i = 0 upto 4:
    draw (9.5u-i*2u, 0.5u) -- (9.5u-i*2u-u, 0.5u) dashed evenly withcolor black withpen pencircle scaled 1pt;
endfor;
for i = 0 upto 3:
    draw (9.5u-i*2u-u, 9.5u) -- (9.5u-i*2u-2u, 9.5u) dashed evenly withcolor black withpen pencircle scaled 1pt;
endfor;

% draw odor source
%drawdot (4u, 5u) withcolor (0.269, 0.543, 0.0) withpen pencircle scaled 10pt;

% draw plume
lambda := 0.4;
wind := 0.5;
numeric pos_x;
numeric pos_y;
for i = 0 upto 1200:
    pos_x := 4;
    pos_y := 5;
    for j = 0 upto i:
        pos_x := pos_x + (wind+lambda*normaldeviate)*0.01;
        pos_y := pos_y + lambda*normaldeviate*0.01;
    endfor;
    if pos_x < 10:
        drawdot (pos_x*u, pos_y*u) withcolor (0.269, 0.543, 0.0) withpen pencircle scaled 1pt;
    fi;
endfor;

% draw wind
drawarrow (3u, 10.3u) -- (7u, 10.3u) withpen pencircle scaled 2pt;
label.top(btex wind etex, (5u, 10.3u));

% draw quadrotor
draw fullcircle scaled 0.3u shifted (9.5u-0.16u, 9.5u+0.16u);
draw fullcircle scaled 0.3u shifted (9.5u+0.16u, 9.5u+0.16u);
draw fullcircle scaled 0.3u shifted (9.5u-0.16u, 9.5u-0.16u);
draw fullcircle scaled 0.3u shifted (9.5u+0.16u, 9.5u-0.16u);
draw (9.5u-0.16u, 9.5u+0.16u) -- (9.5u+0.16u, 9.5u-0.16u);
draw (9.5u+0.16u, 9.5u+0.16u) -- (9.5u-0.16u, 9.5u-0.16u);

% annotations
draw (0u, -0.1u) -- (0u, -0.5u) withpen pencircle scaled 0.5pt;
draw (10u, -0.1u) -- (10u, -0.5u) withpen pencircle scaled 0.5pt;
drawarrow (4u, -0.3u) -- (0u, -0.3u) withpen pencircle scaled 0.5pt;
drawarrow (6u, -0.3u) -- (10u, -0.3u) withpen pencircle scaled 0.5pt;
draw (10.1u, 10u) -- (10.5u, 10u) withpen pencircle scaled 0.5pt;
draw (10.1u, 0u) -- (10.5u, 0u) withpen pencircle scaled 0.5pt;
drawarrow (10.3u, 6u) -- (10.3u, 10u) withpen pencircle scaled 0.5pt;
drawarrow (10.3u, 4u) -- (10.3u, 0u) withpen pencircle scaled 0.5pt;
boxit.len(btex 10 m etex);
len.c = (5u, -0.3u);
boxit.wid(btex 10 m etex);
wid.c = (10.6u, 5u);
drawunboxed(len, wid);
label.top(btex source etex, (4u, 5u+0.1u));
label.bot(btex plume etex, (7u, 5u-0.3u));
label.lft(btex quadrotor etex, (9.2u, 9.7u));












endfig;
end

verbatimtex
\end{document}
etex
