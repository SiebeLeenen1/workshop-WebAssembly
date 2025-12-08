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
