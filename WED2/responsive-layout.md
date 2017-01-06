# Responsive Layout

## Media Queries

> Die Teilnehmer können [...] Fehler in Media-Queries diagnostizieren und beheben.

Syntax:
```css

/*Spezifisches CSS für verschiedene Typen ... */
@media screen {}
@media print {}

/* ... Dimensionen ... */
@media ([width|min-width|max-width]: 375px) {}
@media ([height|min-height|max-height]: 667px) {}
@media ([device-width|min-device-width|max-device-width]: 375px) {}
@media ([device-height|min-device-height|max-device-height]: 667px) {}

/* ... Zustände ... */
@media(orientation: landscape){};

/*... und mehr!*/
@media (min-resolution: 300dpi) {}
@media (-webkit-min-device-pixel-ratio: 2){}
@media (min-color: 1) {}
```

Media Queries können mit Operatoren kominiert werden:

```css
/* AND */
@media (min-width: 20em) and (max-width: 30em) {}
/* OR */
@media (max-width: 10em), (min-width: 20em) and 
       (max-width: 30em), (min-width: 40em) {}
/* NOT */
@media not screen {}
@media not screen and (min-width: 20em) {}
/* ONLY */
@media only screen {}
```


### Typische Trigger Punkte

* Smartphones: 480px / 30em
* Tablets: 768px / 48em
* Desktops: 992px / 62em

## CSS-Pixel vs. Device-Pixel
`px` sind "CSS-Pixel" und eine Abstraktion für uns Entwickler. Das Verhältnis CSS-Pixel / echte Pixel wird durch Zooming verändert (*Device-Pixel-Ratio*).



## Viewports

> Die Teilnehmer können erklären warum das Setzen des Viewports im Meta Tags für responsive Seiten wichtig ist.

```html
<meta name="viewport" content="width=device-width,initial-scale=1">
```

Diese Anweisung ist wichtig um die "Intelligenz“" Mobiler Browser zu unterbinden.

## Responsive images

> Die Teilnehmer können den Code von responsive Image Definitionen interpretieren und erklären wofür responsive Images eingesetzt werden

```html
<img src="" srcset="300.png 300w, 600.png 600w" alt=""
     sizes="(max-width: 320px) 49vw, 100vw">

<img src="image-src.png"
     srcset="image-1x.png 1x, image-2x.png 2x, image-3x.png 3x, image-4x.png 4x">
```

* src ist das fallback
* `nx` Pixeldichte (n device pixel = 1 CSS-Pixel).
* sizes gibt dir grösse des Bilds im Layout an.

```html
<picture>
    <source media="(min-width: 62em)" srcset="Large.png">
    <source media="(min-width: 36em)" srcset="Medium.png">
    <source srcset="Small.png">
    <!-- Fallback -->
    <img src="Small.png" alt="Awesome photo">
</picture>
```
Jede Source verhält sich wie ein `<img>`-Tag, wobei das Media-Query nicht optimiert wird


Problem: Wie können moderne Feature wie Picture in alten Browser genutzt werden.

→  Polyfill/Modernizr
