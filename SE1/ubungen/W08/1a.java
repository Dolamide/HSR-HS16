public boolean equals(Object o) {
    if(o != null && (o instanceof Item)) {
        Item i = (Item) o;
        return (i.getArticleNr() != this.getArticleNr() &&
                i.getAmount() != this.getArticleNr());
    }
    return false;
}
