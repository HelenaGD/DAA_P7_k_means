# Referencias: https://pythondiario.com/2018/08/graficos-en-tercera-dimension-3d-con.html
# Traerse archivos
# scp usuario@10.6.128.144:~/DAA/DAA_P7_k_means/solutions/* .
# Scatter

# importamos las librerias necesarias
from mpl_toolkits.mplot3d import axes3d
import matplotlib.pyplot as plt

name = 'grasp'

# Creamos la figura
fig = plt.figure()
# Creamos el plano 3D
ax1 = fig.add_subplot(111, projection='3d')

# Lee el archivo de texto
with open(name + '.txt') as f:
    # Lee la primera línea como sse
    sse = float(f.readline().strip())
    # Lee la segunda línea como el número de clusters
    num_clusters = int(f.readline().strip())
    # Lee las coordenadas de los centroides
    centroids = []
    for i in range(num_clusters):
        line = f.readline().strip()
        centroid = [float(x) for x in line.split()]
        centroids.append(centroid)
    # Lee los puntos de cada cluster
    clusters = []
    for i in range(num_clusters):
        label = f.readline().strip()
        cluster_points = []
        line = f.readline().strip()
        while line:
            point = [float(x) for x in line.split()]
            cluster_points.append(point)
            line = f.readline().strip()
        clusters.append(cluster_points)

# Agregamos los puntos en el plano 3D
colors = ['g', 'b', 'r', 'c', 'm', 'y', 'k'] # Lista de colores para cada cluster
num_colors = len(colors)
for i in range(num_clusters):
    # Dibuja los centroides
    centroid = centroids[i]
    color_index = i % num_colors # Índice del color a usar (cíclico)
    ax1.scatter(centroid[0], centroid[1], centroid[2], c=colors[color_index], marker='o', s=150)
    # Dibuja los puntos de cada cluster
    cluster_points = clusters[i]
    x = [p[0] for p in cluster_points]
    y = [p[1] for p in cluster_points]
    z = [p[2] for p in cluster_points]
    ax1.scatter(x, y, z, c=colors[color_index], marker='o')

# Agregamos el título con la SSE y el número de clusters
ax1.set_title('SSE: {} - Número de clusters: {}'.format(sse, num_clusters))

# Guardamos la gráfica en un archivo PNG
fig.savefig(name + '.png')

# Mostramos el gráfico
plt.show()
