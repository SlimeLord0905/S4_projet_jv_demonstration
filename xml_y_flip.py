import xml.etree.ElementTree as ET

# Charger le fichier XML
tree = ET.parse("tilemap1.xml")
root = tree.getroot()

# Extraire les index du fichier des tuiles mettre en matrice
indexes = [int(tile.get('index')) for tile in root.iter('tile') if tile.get('index')]
matrix = [indexes[i:i + 80] for i in range(0, len(indexes), 80)]

# matrice complète, incluant le sol
with open("tilemap_output.c", "w") as f:
    f.write("int tilemap[SIZE_Y][SIZE_X] = {\n")
    for row in matrix:
        f.write("    {" + ", ".join(map(str, row)) + "},\n")
    f.write("};\n")

# 36 premières lignes qui se répète à l'infini
with open("repeatable.c", "w") as f:
    f.write("int tilemap[SIZE_Y-9][SIZE_X] = {\n")
    for row in matrix[:36]:
        f.write("{" + ", ".join(map(str, row)) + "},\n")

print(" Fichier complet : 'tilemap_output.c'")
print(" Fichier répétable (36 lignes) : 'repeatable.txt'")
