% Aufgabe 1
d(R):- append(X, X, R).
palindrome(Q):- reverse(Q, Q).

%Aufgabe 2

%Aufgabe 3
% Grusig
toptail([_|[]],[], _).

toptail([_|L], [_|T], _):-
    toptail(L, T, []).

toptail([_|L],OutList):-
    toptail(L, OutList, _).

% Schöner:
toptail(InList, OutList):-
append([_|OutList],[_], InList).
