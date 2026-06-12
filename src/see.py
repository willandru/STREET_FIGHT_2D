import os

# extensiones a analizar
EXTENSIONS = {".h", ".cpp"}

# patrones peligrosos
BAD_PATTERNS = [
    "#define time",
    "#define clock",
    "#define min",
    "#define max"
]

def scan_file(path):
    print("\n" + "=" * 80)
    print(f"FILE: {path}")
    print("=" * 80)

    try:
        with open(path, "r", encoding="utf-8", errors="ignore") as f:
            lines = f.readlines()

        # imprimir primeras 10 líneas
        print("\n--- FIRST 10 LINES ---")
        for i, line in enumerate(lines[:10]):
            print(f"{i+1:02d}: {line.rstrip()}")

        # buscar patrones peligrosos
        print("\n--- DETECTED ISSUES ---")
        found = False

        for i, line in enumerate(lines):
            for pattern in BAD_PATTERNS:
                if pattern in line:
                    print(f"[LINE {i+1}] {pattern} -> {line.strip()}")
                    found = True

        if not found:
            print("No suspicious macros found.")

    except Exception as e:
        print(f"ERROR reading file: {e}")


def scan_project(root_dir):
    for root, _, files in os.walk(root_dir):
        for file in files:
            if any(file.endswith(ext) for ext in EXTENSIONS):
                full_path = os.path.join(root, file)
                scan_file(full_path)


if __name__ == "__main__":
    project_path = "."  # cambia esto si quieres otra carpeta
    scan_project(project_path)