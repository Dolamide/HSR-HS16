Knoten suchen(Knoten p, int x) {
    if (p == null)
        return null;
    if (x < p.key)
        return suchen(p.leftson, x);
    else if (x > p.key)
        return suchen(p.rightson,x);
    return p;
}

public void einfuegen(int k) {
    wurzel = einfuegen(wurzel,k); //nicht public: friendly
}

Knoten einfuegen(Knoten p, int k) {
    if (p == null)
        return new Knoten(k);
    else if (k < p.key)
        p.leftson = einfuegen(p.leftson,k);
    else if (k > p.key)
        p.rightson = einfuegen(p.rightson,k);
    return p;
}

public void entfernen(int k) {
    wurzel = entfernen(wurzel,k);
}

Knoten entfernen(Knoten p, int k) {
    if (p == null)
        return p;
    if (k < p.key)
        p.leftson = entfernen(p.leftson,k);
    else if (k > p.key)
        p.rightson = entfernen(p.rightson,k);
    else {
        if (p.leftson == null)
            return p.rightson;
        if (p.rightson == null)
            return p.leftson;
        Knoten q = vatersymnach(p);
        if (q == p) {
            p.key = p.rightson.key;
            q.rightson = q.rightson.rightson;
        } else {
            p.key = q.leftson.key;
            q.leftson = q.leftson.rightson;
        }
    }
    return p;
}

Knoten vatersymnach (Knoten p) {
    if (p.rightson.leftson != null) {
        p = p.rightson;
        while (p.leftson.leftson != null)
            p = p.leftson;
    }
    return p;
}

String inorder(Node subTreeRoot) {
    if (p == null) {
        return "";
    }
    return inorder(p.getLeft()) +
            "(" + p.toString() + ")" +
            inorder(p.getRight());
}
