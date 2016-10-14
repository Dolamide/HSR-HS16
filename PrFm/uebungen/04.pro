%  Exercise  1.1 Which of the following sequences of characters are atoms, which are variables, and which are neither?

vINCENT                     % atom
Footmassage                 % variable
variable23                  % atom
Variable2000                % variable
big_kahuna_burger           % atom
’big  kahuna  burger’       % atom
big  kahuna  burger         % neither
’Jules’                     % atom
_Jules                      % variable
’_Jules’                    % atom


%  Exercise  1.2 Which of the following sequences of characters are atoms, which are variables,
%   which are complex terms, and which are not terms at all? Give the functor and arity of each complex term.

Atoms, Variables, complex (with functor and arity) terms and not terms.

loves(Vincent,mia)                       % complex, functor loves, arity 2
’loves(Vincent,mia)’                     % atom (X)
Butch(boxer)                             % not a term
boxer(Butch)                             % complex, functor boxer, arity 2
and(big(burger),kahuna(burger))          % complex, functor and,  arity 2 (with 2 other complex with arity 1 - containing atoms)
and(big(X),kahuna(X))                    % complex, functor and, arity 2 (with 2 other complex with arity 1 - containing variables)
_and(big(X),kahuna(X))                   % not a term
(Butch  kills  Vincent)                  % not a term
kills(Butch  Vincent)                    % not a term (missing comma) (X)
kills(Butch,Vincent                      % not a term (missing ')')

% Exercise  1.3 How many facts, rules, clauses, and predicates are there in the
% following knowledge base? What are the heads of the rules, and what are the goals they contain?

% All facts and rules are clauses

woman(vincent).                          % fact: predicate woman
woman(mia).                              % fact: predicate woman
man(jules).                              % fact: predicate man
person(X):- man(X); woman(X).            % rule: (head: person(X), body/goals: man(X); woman(X)
loves(X,Y):- father(X,Y).                % rule: (head: loves(X, Y), body/goals: father(X, Y))
father(Y,Z):- man(Y), son(Z,Y).          % rule: (head: father(Y, Z), body/goals: man(Y), son(Z, Y))
father(Y,Z):- man(Y), daughter(Z,Y).     % rule: (head: father(Y, Z), body/goals: man(Y), daughter(Z, Y))

% -> 3 Facts, 4 Rules, 7 clauses and 7 predicates

%  Exercise  1.4 Represent the following in Prolog:
% Butch is a killer.
% Mia and Marsellus are married.
% Zed is dead.
% Marsellus kills everyone who gives Mia a footmassage.
% Mia loves everyone who is a good dancer.
% Jules eats anything that is nutritious or tasty.

killer(butch).
married(mia, marsellus).
dead(zed).
kills(marsellus, X):- givesFootMassage(X, Mia).
loves(mia, Y):- goodDancer(Y).
eats(jules, X):- nutritious(X); tasty(X).

% Exercise  1.5 Suppose we are working with the following knowledge base:

wizard(ron).
hasWand(harry).
quidditchPlayer(harry).
wizard(X):- hasBroom(X), hasWand(X).
hasBroom(X):- quidditchPlayer(X).

%  How does Prolog respond to the following queries?

wizard(ron).           % yes
witch(ron).            % undefined procedure
wizard(hermione).      % no
witch(hermione).       % undefined procedure
wizard(harry).         % yes
wizard(Y).             % Y = ron, Y = harry, no
witch(Y).              % undefined procedure

% Exercise  2.1 Which of the following pairs of terms unify?
% Where relevant, give the variable instantiations that lead to successful unification.


bread  =  bread                                    % true
’Bread’  =  bread                                  % false
’bread’  =  bread                                  % true
Bread  =  bread                                    % Bread = bread
bread  =  sausage                                  % false
food(bread)  =  bread                              % false
food(bread)  =  X                                  % X = food(bread)
food(X)  =  food(bread)                            % X = bread
food(bread,X)  =  food(Y,sausage)                  % X = sausage, Y = bread
food(bread,X,beer)  =  food(Y,sausage,X)           % false
food(bread,X,beer)  =  food(Y,kahuna_burger)       % false
food(X)  =  X                                      % X = food(X)
meal(food(bread),drink(beer))  =  meal(X,Y)        % X = food(bread), Y = drink(beer)
meal(food(bread),X)  =  meal(X,drink(beer))        % false

% Exercise  2.2 We are working with the following knowledge base:

house_elf(dobby).
witch(hermione).
witch('McGonagall').
witch(rita_skeeter).
magic(X):- house_elf(X).
magic(X):- wizard(X).
magic(X):- witch(X).

% Which of the following queries are satisfied? Where relevant, give all the variable instantiations that lead to success.

?-  magic(house_elf).                               % false (X)
?-  wizard(harry).                                  % false
?-  magic(wizard).                                  % false
?-  magic(’McGonagall’).                            % true
?-  magic(Hermione).                                % Hermione = dobby, Hermione = hermione, Hermione = 'McGonagall', Hermione = rita_skeeter

% Draw the search tree for the query magic(Hermione) . (X)

%  Exercise  2.3 Here is a tiny lexicon (that is, information about individual words) and a
% mini grammar consisting of one syntactic rule
% (which defines a sentence to be an entity consisting of five words in
% the following order: a determiner, a noun, a verb, a determiner, a noun).

word(determiner,a).
word(determiner,every).
word(noun,criminal).
word(noun,'big kahuna burger').
word(verb,eats).
word(verb,likes).

sentence(Word1,Word2,Word3,Word4,Word5):-
word(determiner,Word1),
word(noun,Word2),
word(verb,Word3),
word(determiner,Word4),
word(noun,Word5).

% What query do you have to pose in order to find out which sentences
% the grammar can generate? List all sentences that this grammar can
% generate in the order that Prolog will generate them in.


% Exercise  2.4 Here are six Italian words:
% TBD
