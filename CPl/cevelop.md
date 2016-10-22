# Cevelop

## "No such file bei CUTE Test für static library"

```
fatal error: xyx.h: No such file or directory
```

Das Problem ist typischerweise, dass die gesuchte Datei nicht im Root der Library ist. Entweder kann der include angepasst werden (Bsp. ``#include "src/sayhello.h"``) oder die Dateien in das Hauptverzeichnis der Library verschieben.
