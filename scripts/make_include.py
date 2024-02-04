import os
import shutil

script_dir = os.path.dirname(os.path.realpath(__file__))
source_dir = os.path.join(script_dir, "..", "src")
include_dir = os.path.join(script_dir, "..", "include")

# Remove include directory
if os.path.exists(include_dir):
    shutil.rmtree(include_dir)

# Create include directory
os.mkdir(include_dir)

# Copy all header files recursively
for root, dirs, files in os.walk(source_dir):
    for file in files:
        if not file.endswith(".h"):
            continue

        if file == "Entry.h":
            continue

        source_file = os.path.join(root, file)
        source_file_relpath = os.path.relpath(source_file, source_dir)
        include_file = os.path.join(include_dir, source_file_relpath)

        with open(source_file, "r", encoding="utf-8") as f:
            source_content = f.read()

        # Replace __declspec(dllexport) with __declspec(dllimport)
        include_content = source_content.replace("__declspec(dllexport)", "__declspec(dllimport)")

        os.makedirs(os.path.dirname(include_file), exist_ok=True)

        # Write include file
        with open(include_file, "w", encoding="utf-8") as f:
            f.write(include_content)
