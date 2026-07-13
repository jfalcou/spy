//==================================================================================================
//  Copacabana - Common CMake Package Tools
//  Copyright : Copacabana Project Contributors
//  SPDX-License-Identifier: BSL-1.0
//==================================================================================================
function escapeHtml(str) {
    const escapeMap = {
        '&': '&amp;',
        '<': '&lt;',
        '>': '&gt;',
        '"': '&quot;',
        "'": '&#39;',
    };
    return str.replace(/[&<>"']/g, match => escapeMap[match]);
}

function removeANSIEscapeCodes(inputString) {
    const ansiEscapeRegex = /\x1B\[[0-9;]*[A-Za-z]/g;
    return inputString.replace(ansiEscapeRegex, '');
}

async function postCE(url, jsonObject) {
  try {
    const response = await fetch("https://www.godbolt.org/api/compiler/" + url + "/compile", {
      method: "POST",
      headers: {
        'Accept': 'application/json',
        'Content-Type': 'application/json',
      },
      body: JSON.stringify(jsonObject)
    });

    if (!response.ok) {
      throw new Error(`HTTP error! Status: ${response.status}`);
    }

    const actualResponse = await response.json();
    const stdoutLines = actualResponse.stdout.map(entry => escapeHtml(removeANSIEscapeCodes(entry.text))).join("<br/>");
    const stderrLines = actualResponse.buildResult.stderr.map(entry => escapeHtml(removeANSIEscapeCodes(entry.text))).join("<br/>");
    return [stdoutLines, stderrLines];
  } catch (error) {
    console.error("Error during postCE:", error);
  }
}

class SendToGodbolt extends HTMLElement {
  constructor() {
    super();
    this.onclick = this.openCE;
  }

  static library  = "";
  static compiler = "";
  static option   = "";
  static title = "Run with Compiler Explorer"
  static icon = `<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 64 64" width="64" height="64">
                 <switch><g><path d="M58.6 46.5c-.3-.5-.3-1.2 0-1.7.3-.6.7-1.3 1-2 .2-.5-.1-1-.7-1h-5.8c-.6 0-1.2.3-1.4.8-.7 1.1-1.6 2.2-2.6 3.2-3.7 3.7-8.6 5.7-13.9 5.7-5.3 0-10.2-2-13.9-5.7-3.8-3.7-5.8-8.6-5.8-13.9s2-10.2 5.8-13.9c3.7-3.7 8.6-5.7 13.9-5.7 5.3 0 10.2 2 13.9 5.7 1 1 1.9 2.1 2.6 3.2.3.5.9.8 1.4.8h5.8c.5 0 .9-.5.7-1-.3-.7-.6-1.3-1-2-.3-.5-.3-1.2 0-1.7l1.9-3.5c.4-.7.3-1.5-.3-2.1l-4.9-4.9c-.6-.6-1.4-.7-2.1-.3l-3.6 2c-.5.3-1.2.3-1.7 0-1.7-.9-3.5-1.7-5.4-2.2-.6-.2-1-.6-1.2-1.2l-1.1-3.9C40.1.5 39.5 0 38.7 0h-6.9C31 0 30.2.5 30 1.3l-1.1 3.9c-.2.6-.6 1-1.2 1.2-1.9.6-3.6 1.3-5.3 2.2-.5.3-1.2.3-1.7 0l-3.6-2c-.7-.4-1.5-.3-2.1.3l-4.9 4.9c-.6.6-.7 1.4-.3 2.1l2 3.6c.3.5.3 1.2 0 1.7-.9 1.7-1.7 3.5-2.2 5.3-.2.6-.6 1-1.2 1.2l-3.9 1.1c-.7.2-1.3.9-1.3 1.7v6.9c0 .8.5 1.5 1.3 1.7l3.9 1.1c.6.2 1 .6 1.2 1.2.5 1.9 1.3 3.6 2.2 5.3.3.6.3 1.2 0 1.7l-2 3.6c-.4.7-.3 1.5.3 2.1L15 57c.6.6 1.4.7 2.1.3l3.6-2c.6-.3 1.2-.3 1.7 0 1.7.9 3.5 1.7 5.3 2.2.6.2 1 .6 1.2 1.2l1.1 3.9c.2.7.9 1.3 1.7 1.3h6.9c.8 0 1.5-.5 1.7-1.3l1.1-3.9c.2-.6.6-1 1.2-1.2 1.9-.6 3.6-1.3 5.4-2.2.5-.3 1.2-.3 1.7 0l3.6 2c.7.4 1.5.3 2.1-.3l4.9-4.9c.6-.6.7-1.4.3-2.1l-2-3.5z" fill="#67c52a"/><path d="M23.5 37.7v4.4h23.8v-4.4H23.5zm0-7.8v4.4h19.6v-4.4H23.5zm0-7.9v4.4h23.8V22H23.5z" fill="#3c3c3f"/></g></switch></svg>
                 </svg>`

  static getLibs() {
    let libs = [];
    if (SendToGodbolt.library) {
      const parts = SendToGodbolt.library.split(':');
      parts.forEach(libName => {
        if(libName.trim().length > 0) {
          libs.push({ "id": libName, "version": "trunk" });
        }
      });
    }
    libs.push({ "id": "tts", "version": "trunk" });
    return libs;
  }

  static injectCSS() {
      if (document.getElementById("godbolt-button-styles")) return;
      const style = document.createElement("style");
      style.id = "godbolt-button-styles";
      style.innerHTML = `
        doxygen-awesome-godbolt-button {
            background: var(--fragment-background, var(--page-background-color, #ffffff));
            border: 1px solid var(--separator-color, #cccccc);
            border-radius: var(--border-radius-small, 4px);

            position: absolute;
            top: calc(var(--fragment-padding-y, .4rem) + 4px);
            /* Offset adjusted for the wider 30px native button + 6px gap */
            right: calc(var(--fragment-padding-x, .4rem) + 36px);

            /* Increased to 30px to match the native button's bounding box exactly */
            width: 30px;
            height: 30px;
            box-sizing: border-box;
            display: flex;
            justify-content: center;
            align-items: center;

            cursor: pointer;
            z-index: 2;
            opacity: 0;
            transition: opacity .2s ease, background-color .2s ease;
        }
        .doxygen-awesome-fragment-wrapper:hover doxygen-awesome-godbolt-button {
            opacity: 1;
        }
        doxygen-awesome-godbolt-button:hover {
            background-color: var(--fragment-background-hover, var(--primary-light-color, #f0f0f0));
        }
        doxygen-awesome-godbolt-button svg {
            /* Scaled proportionally to fit the new 30px container */
            width: 20.5px;
            height: 20.5px;

            /* CSS magic: Make it grey and slightly faded by default */
            filter: grayscale(100%) opacity(60%);
            transition: filter 0.2s ease, opacity 0.2s ease;
        }
        doxygen-awesome-godbolt-button:hover svg {
            /* Snap back to full vibrant color when hovered */
            filter: grayscale(0%) opacity(100%);
        }
        .godbolt-output-block {
            margin-top: 10px;
        }
      `;
      document.head.appendChild(style);
  }

  static init(lib, compil, opts) {
    $(function () {
      $(document).ready(function () {
        SendToGodbolt.library  = lib;
        SendToGodbolt.compiler = compil;
        SendToGodbolt.option   = opts;

        SendToGodbolt.injectCSS();

        const fragments = document.getElementsByClassName("fragment");
        for (const fragment of fragments) {
          let wrapper = fragment.parentNode;

          if (!wrapper.classList.contains("doxygen-awesome-fragment-wrapper")) {
            wrapper = document.createElement("div");
            wrapper.className = "doxygen-awesome-fragment-wrapper";
            fragment.parentNode.replaceChild(wrapper, fragment);
            wrapper.appendChild(fragment);
          }

          const godboltBtn = document.createElement("doxygen-awesome-godbolt-button");
          godboltBtn.innerHTML = SendToGodbolt.icon;
          godboltBtn.title = SendToGodbolt.title;

          wrapper.appendChild(godboltBtn);

          const content = fragment.cloneNode(true);
          content.querySelectorAll(".lineno, .ttc").forEach((node) => { node.remove(); });
          let textContent = content.textContent;

          let numberOfTrailingNewlines = 0;
          while (textContent.charAt(textContent.length - (numberOfTrailingNewlines + 1)) == '\n') {
            numberOfTrailingNewlines++;
          }

          textContent = textContent.substring(0, textContent.length - numberOfTrailingNewlines);

          if (textContent.includes("main(")) {
            let data = {
              "source": textContent,
              "compiler": SendToGodbolt.compiler,
              "options": {
                "userArguments": SendToGodbolt.option,
                "compilerOptions": { "executorRequest": true },
                "filters": { "execute": true },
                "libraries": SendToGodbolt.getLibs()
              },
              "lang": "c++",
              "allowStoreCodeDebug": true
            };

            postCE(SendToGodbolt.compiler, data).then((out) => {
              if(!out) return;
              const [display, error] = out;
              const output = document.createElement("dl");

              if (display && display.length != 0) {
                output.className = "section success";
                output.innerHTML = display;
              } else {
                output.className = "section compiler";
                output.innerHTML = error || "Compilation failed with unknown error.";
              }

              const block = document.createElement("div");
              block.className = "godbolt-output-block";
              block.innerHTML = "<b>Output:</b><br/>";
              block.appendChild(output);

              wrapper.parentNode.insertBefore(block, wrapper.nextSibling);
            });
          }
        }
      });
    });
  }

  openCE() {
    const wrapper = this.closest('.doxygen-awesome-fragment-wrapper');
    const fragment = wrapper ? wrapper.querySelector('.fragment') : this.previousSibling;

    if(!fragment) return;

    const content = fragment.cloneNode(true);
    content.querySelectorAll(".lineno, .ttc").forEach((node) => {
      node.remove();
    });
    let textContent = content.textContent;

    let numberOfTrailingNewlines = 0;
    while (textContent.charAt(textContent.length - (numberOfTrailingNewlines + 1)) == '\n') {
      numberOfTrailingNewlines++;
    }
    textContent = textContent.substring(0, textContent.length - numberOfTrailingNewlines);

    let data = {
      "sessions": [
        {
          "id": 1,
          "language": "c++",
          "source": textContent,
          "compilers": [],
          "executors": [
            {
              "compiler":
              {
                  "id": SendToGodbolt.compiler,
                  "libs":  SendToGodbolt.getLibs(),
                  "options": SendToGodbolt.option
              }
            }
          ]
        }
      ]
    };

    let body = JSON.stringify(data);
    let state = btoa(body);
    let url = "https://godbolt.org/clientstate/" + encodeURIComponent(state);

    window.open(url, "_blank");
  }
}

customElements.define("doxygen-awesome-godbolt-button", SendToGodbolt);