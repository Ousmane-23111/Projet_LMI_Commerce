import matplotlib.pyplot as plt
import numpy as np

# Tailles de données testées
tailles = [100, 1000, 10000]

# Résultats benchmarks (en ms) — remplacez par vos vraies valeurs
tab_statique  = [0.1, 0.8, 8.5]
tab_dynamique = [0.2, 1.2, 12.0]
liste_chainee = [0.3, 2.5, 25.0]
abr           = [0.1, 0.9, 9.5]
tas           = [0.1, 0.7, 7.5]

# ===== COURBE 1 : Temps en fonction de n =====
plt.figure(figsize=(10, 6))
plt.plot(tailles, tab_statique,  'b-o', label='Tableau statique')
plt.plot(tailles, tab_dynamique, 'r-o', label='Tableau dynamique')
plt.plot(tailles, liste_chainee, 'g-o', label='Liste chainee')
plt.plot(tailles, abr,           'm-o', label='ABR')
plt.plot(tailles, tas,           'y-o', label='Tas binaire')
plt.xlabel('Nombre de produits (n)')
plt.ylabel('Temps (ms)')
plt.title('Temps insertion en fonction de n')
plt.legend()
plt.grid(True)
plt.savefig('courbe_insertion.png')
plt.show()

# ===== COURBE 2 : Échelle logarithmique =====
plt.figure(figsize=(10, 6))
plt.loglog(tailles, tab_statique,  'b-o', label='Tableau statique')
plt.loglog(tailles, tab_dynamique, 'r-o', label='Tableau dynamique')
plt.loglog(tailles, liste_chainee, 'g-o', label='Liste chainee')
plt.loglog(tailles, abr,           'm-o', label='ABR')
plt.loglog(tailles, tas,           'y-o', label='Tas binaire')
plt.xlabel('Nombre de produits (n)')
plt.ylabel('Temps (ms)')
plt.title('Temps insertion - Échelle logarithmique')
plt.legend()
plt.grid(True)
plt.savefig('courbe_insertion_log.png')
plt.show()

print("Courbes générées avec succès !")