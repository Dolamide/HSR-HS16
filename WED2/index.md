# Inhalt

{{TOC}}

# Übersicht

* NodeJS / express
* REST
* Fluid Page Layout (FlexBox)
* Responsive Page Laytout
* CSS "Engineering" (Sass, Best Pracitces usw.)
* UCD
* Web Security
* OO in JS
* Typescript
* ES6
* Unit-Testing

Paralell dazu: Mini-Projekt

# Weiters
## Handlebars
"Magie" von `Layout.hbr`: Wenn ein File `Layout.hbr` im Ordner `views/` existiert, dann sollte dies eine Expression `{{{body}}}` enthalten.
Wird dann `res.render('myItemView', itemDataJsonObject)` aufgerufen, so wird zuerst diese Template `Layout.hbr` aufgerufen (mit `itemDataJsonObject`). Zum Auflösen der Expression `{{{body}}}` wird dann `myItemView.hbr` (mit `itemDataJsonObject`) aufgerufen.
