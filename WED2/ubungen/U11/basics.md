# ES6 Literale 1

```js
function fn1(name, age) {
  return {
    name,
    [age]: age,
  };
}

fn1('Peter', 12);
// Resultat: {'name': 'Peter', '12': 12}
```

Grund: `name` ist Shorthand - dabei wir der Name der Variable gleich dem Namen im Objekt. `[age]` dagegen nimmt den Wert von `age` als Key (umgewandelt in String) 

# ES6 Literale 2

```js
function newParagraph(initText) {
  let myParagraph = initText;
  return {
    get paragraph() {
      return myParagraph;
    },
    appendText(addText) {
      myParagraph += addText;
    },
  };
}

const p = newParagraph('lorem ');
p.appendText('impsum');
console.log(p.paragraph);
p.paragraph = 'other text';
console.log(p.paragraph);
```

* Was ist der Output?

```
lorem impsum 
lorem impsum 
undefined
```

* Erklären Sie das Resultat
    * Kein Setter definiert -> Daher bleibt die Zuweisung undefiniert.

* Was macht newParagraph?
* Welche Properties hat der Wert der Variablen p?
* Welche Methoden hat der Wert der Variablen p?
* Was ist der Effekt von `p.paragraph = 'other text';`
