# Simulazione Monte Carlo dell'accettanza geometrica

Simulazione Monte Carlo in **ROOT** (CERN) per la stima dell'accettanza geometrica di un rivelatore cilindrico rispetto a una sorgente radioattiva isotropa (puntiforme ed estesa a disco), con verifica tramite fit bidimensionale della formula analitica.

Progetto realizzato per il C.d.S. in Fisica — Università degli Studi di Catania (A.A. 2023-2024).

## Struttura del repository
* `macro/` — Macro C++ per ROOT:
  * `accettanza_puntiforme.C` — Simulazione ($10^7$ eventi) per sorgente puntiforme sull'asse del rivelatore, con istogrammi 3D di controllo dell'isotropia e mappa 2D sul rivelatore.
  * `accettanza_disco.C` — Estensione a sorgente estesa a disco di raggio $r$ ($10^7$ eventi) con campionamento radiale lineare ($\rho$) e mappa 2D su sorgente e rivelatore.
  * `accettanza_puntiforme_andamento.C` — Andamento dell'accettanza $\epsilon(D)$ al variare della distanza $D$ per diversi raggi $R$.
  * `accettanza_super.C` — Ricostruzione della superficie 2D $\epsilon(D, R)$ e best-fit con la funzione analitica $\epsilon(D, R) = p_0 \left(1 - \frac{D}{\sqrt{D^2 + R^2}}\right)$.
* `grafici/` — Immagini dei grafici 2D e 3D prodotti dalle simulazioni.
* `relazione/` — Relazione completa in formato PDF (`accettanza_geometrica.pdf`).

## Requisiti
* **ROOT** (CERN)

## Come eseguire le macro
Dalla cartella `macro/`, eseguire la simulazione desiderata:
```bash
cd macro
root -l accettanza_puntiforme.C
```
*(Per `accettanza_puntiforme.C` e `accettanza_disco.C` il programma chiede da terminale i valori di $D$, $R$ e $r$).*

## Risultati principali
* **Sorgente puntiforme** ($R = 0.4\text{ m}$, $D = 2\text{ m}$): $\epsilon_{\text{geom}} = (9.750 \pm 0.022) \cdot 10^{-3}$
* **Sorgente a disco** ($R = 0.7\text{ m}$, $r = 0.4\text{ m}$, $D = 2\text{ m}$): $\epsilon_{\text{geom}} = (2.743 \pm 0.037) \cdot 10^{-2}$
* **Fit superficie 2D** $\epsilon(D, R)$: parametro $p_0 = 0.4716 \pm 0.0048$ (valore teorico atteso $0.5$)