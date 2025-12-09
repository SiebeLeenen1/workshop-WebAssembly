# workshop-WebAssembly
Workshop voor IT-Tools
# Van C naar WebAssembly – IT Tools 2 Workshop

**Duur:** 2 uur  
**Niveau:** Beginner → Gemiddeld  
**Doel:** Begrijp en ervaar de kracht van WebAssembly via C.

---

## 📋 Leerdoelen
- Compileer C‑code naar WebAssembly (Wasm)  
- Voer `.wasm` uit en communiceer ermee vanuit JavaScript  
- **Vergelijk prestaties van Wasm vs JavaScript**  
- Verwerk tekst en beheer geheugenuitwisseling tussen JS en C  

---
## Vereisten
Maak een nieuwe map aan in C:/user/documenten met naam emsdk en clone deze repo:
git clone https://github.com/emscripten-core/emsdk.git
Installeer dit vooraf:
```bash
cd emsdk
emsdk install latest
emsdk activate latest
emsdk_env.sh
```

Activeer Emscripten in je huidige terminal sessie:
```bash
.\emsdk_env.ps1
```


Controleer met:
```bash
emcc -v
```

Als je de workshop repo nog niet hebt gecloned: https://github.com/SiebeLeenen1/workshop-WebAssembly.git

In de map workshop_WebAssembly
```bash
npm install
```
Controleer met:
```bash
npm -v
```
---

## Overzicht van oefeningen
| Map | Beschrijving |
|------|---------------|
| 01_hello_c | Compileer & voer je eerste C‑code uit in de browser |
| 02_math_function | Exporteer & roep een gecompileerde C‑functie aan vanuit JS |
| 03_js_vs_wasm_benchmark | Vergelijk de snelheid van JavaScript en WebAssembly |
| 04_reverse_string | Manipuleer strings met lineair geheugen |
| 05 Demo | Foto manipulatie met pixelation, sepia en edge detection |

## Benchmark‑doel
Deelnemers meten de uitvoeringstijd van een grote berekening, zowel in JS als in gecompileerde C (Wasm).  
We gebruiken `performance.now()` om de tijden te vergelijken.

---

## 🚀 Na de Workshop
- Experimenteer met optimalisatie‑vlaggen zoals `-O3` of `-Oz`  
- Ontdek Rust → Wasm  
- Probeer WASI voor uitvoering buiten de browser  

© IT‑Tools‑2 Workshop 2025
