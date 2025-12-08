# Exercise 02: Add Function - JavaScript ↔ C Communication

## 🎯 Goal
Export a C function to JavaScript and call it from the browser.

## 📝 Assignment
1. Create a C function that adds two numbers
2. Export it so JavaScript can call it
3. Create a web interface with a button that calls the function and displays the result

## 🔨 Steps

### Step 1: Write the C function
Create `math.c`:
```c
#include <emscripten/emscripten.h>

EMSCRIPTEN_KEEPALIVE
int add(int a, int b) {
    return a + b;
}
```

**Important:** 
- `EMSCRIPTEN_KEEPALIVE` prevents the function from being removed during optimization
- The function must be exported explicitly

### Step 2: Compile with exported functions
```bash
emcc math.c -O3 -s "EXPORTED_FUNCTIONS=['_add']" -o math.js
```

This generates:
- `math.js` - JavaScript wrapper with Module object
- `math.wasm` - WebAssembly binary

### Step 3: Create HTML interface
Create `math.html`:
```html
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Addition via WebAssembly</title>
  </head>
  <body>
    <h1>Addition via WebAssembly</h1>
    <button id="run">Run Demo</button>
    <script>
      var Module = {
        onRuntimeInitialized: function() {
          document.getElementById("run").onclick = () => {
            const result = Module._add(12, 8);
            alert(`12 + 8 = ${result}`);
            console.log("Result from C:", result);
          };
        }
      };
    </script>
    <script src="math.js"></script>
  </body>
</html>
```

**Key points:**
- Define `Module` object BEFORE loading `math.js`
- Use `Module._add()` to call the C function (note the underscore prefix)
- `onRuntimeInitialized` ensures WebAssembly is ready before calling functions

### Step 4: Run the application
```bash
npm run build:add
npm run serve:add
```

Open `http://localhost:8081/math.html`

## ✅ Success criteria
- Clicking the button shows an alert: "12 + 8 = 20"
- The console shows the result
- You understand how to export and call C functions from JavaScript

## 💡 Bonus challenges
- Create a `subtract`, `multiply`, or `divide` function
- Add input fields to let users enter their own numbers
- Try passing different data types (floats, negative numbers)
- Export multiple functions in one compilation
