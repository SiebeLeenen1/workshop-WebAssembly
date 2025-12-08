# Exercise 04: Reverse String - Memory Management

## 🎯 Goal
Learn how to pass strings between JavaScript and C using WebAssembly's linear memory.

## 📝 Assignment
1. Create a C function that reverses a string
2. Handle memory allocation and deallocation
3. Pass strings from JavaScript to C and back

## 🔨 Steps

### Step 1: Write the C string reversal function
Create `reverse.c`:
```c
#include <emscripten/emscripten.h>
#include <string.h>
#include <stdlib.h>

EMSCRIPTEN_KEEPALIVE
char* reverse(const char* str) {
    int len = strlen(str);
    char* result = (char*)malloc(len + 1);
    
    for (int i = 0; i < len; i++) {
        result[i] = str[len - 1 - i];
    }
    result[len] = '\0';
    
    return result;
}
```

**Important:**
- We allocate memory for the result string
- JavaScript must free this memory after use to prevent leaks
- The null terminator `\0` is crucial

### Step 2: Compile with memory functions
```bash
emcc reverse.c -O3 -s EXPORTED_FUNCTIONS='["_reverse","_malloc","_free"]' -o reverse.js
```

**Why export malloc and free?**
- JavaScript needs to allocate memory in WebAssembly's linear memory
- JavaScript must free memory to prevent leaks

### Step 3: Create the HTML interface
Create `index.html`:
```html
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Reverse a String</title>
  </head>
  <body>
    <h1>Reverse a String</h1>
    <label for="txt">Input: <input id="txt" value="WebAssembly!" /></label>
    <button id="btn">Reverse</button>
    <p id="out"></p>
    <script src="reverse.js"></script>
    <script src="script.js"></script>
  </body>
</html>
```

### Step 4: Write the JavaScript bridge
Create `script.js`:
```javascript
var Module = {
  onRuntimeInitialized: function() {
    document.getElementById("btn").onclick = () => {
      const input = document.getElementById("txt").value;
      
      // Allocate memory for input string
      const inputLen = lengthBytesUTF8(input) + 1;
      const inputPtr = Module._malloc(inputLen);
      
      // Copy JavaScript string to WebAssembly memory
      stringToUTF8(input, inputPtr, inputLen);
      
      // Call the C function
      const resultPtr = Module._reverse(inputPtr);
      
      // Read the result from WebAssembly memory
      const result = UTF8ToString(resultPtr);
      
      // Display result
      document.getElementById("out").textContent = `Result: ${result}`;
      
      // Free allocated memory
      Module._free(inputPtr);
      Module._free(resultPtr);
    };
  }
};
```

**Memory management flow:**
1. Allocate memory in Wasm for input string
2. Copy JS string to Wasm memory
3. Call C function (returns pointer to result)
4. Read result from Wasm memory back to JS
5. Free both input and result memory

### Step 5: Run the application
```bash
npm run build:reverse
npm run serve:reverse
```

Open `http://localhost:8081/index.html`

## ✅ Success criteria
- Typing in the input and clicking "Reverse" shows the reversed string
- Memory is properly allocated and freed (no leaks)
- You understand how linear memory works in WebAssembly
- You can pass strings between JavaScript and C

## 💡 Bonus challenges
- Add validation (empty string, special characters)
- Create other string functions (uppercase, lowercase, palindrome check)
- Show both original and reversed string
- Add a "Clear" button
- Handle Unicode characters (emoji, accented characters)
- Implement a more complex algorithm (ROT13, Caesar cipher)

## 🧠 Key concepts

### Linear Memory
WebAssembly uses a contiguous block of memory (like an array). JavaScript and C share this memory:
- C writes to memory at certain addresses
- JavaScript reads from those addresses
- Both need to agree on the format

### Helper functions (provided by Emscripten)
- `lengthBytesUTF8(str)` - Get byte length of string in UTF-8
- `stringToUTF8(str, ptr, maxBytes)` - Write JS string to Wasm memory
- `UTF8ToString(ptr)` - Read C string from Wasm memory to JS

### Memory management
- Always `free()` what you `malloc()`
- Both input and output need to be freed
- Memory leaks can crash the application over time
