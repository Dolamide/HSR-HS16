Spick
```prolog
reverse(Xs, Ys) :-
	reverse(Xs, [], Ys, Ys).

reverse([], Ys, Ys, []).
reverse([X|Xs], Rs, Ys, [_|Bound]) :-
	reverse(Xs, [X|Rs], Ys, Bound).

```
->
```
palindrome(L):- reverse(L, L).    
```
Alternativ:
```
palindrome(L):- palindrome(L, []).

palindrome([EL|SRC], DST):-
    NEW = [EL| DST],
    (
    	SRC = NEW;
    	SRC = DST;
    	palindrome(SRC, NEW)
    ).
```


append
```prolog
% append(List1, List2, List1AndList2)
% List1AndList2 is the *concatenation* of List1 and List2
append([], L, L).
append([H|T], L, [H|R]) :-
	append(T, L, R).

```
memberof

delete
