

find . -name "*.pcx" -exec sh -c '
for f; do
    convert "$f" -transparent magenta "${f%.pcx}.png"
done
' sh {} +
