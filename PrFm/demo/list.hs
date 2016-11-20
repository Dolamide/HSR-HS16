data Lst a = Nil |  Cons a (Lst a)
    deriving (Show)

l1 = Cons 'a' (Cons 'b' Nil)
len Nil = 0
len (Cons x xs) = 1 + (len xs)
