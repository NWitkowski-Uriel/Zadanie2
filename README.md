# ReadMe for zadanie2.C

## Opis programu

Program `zadanie2.C` służy do analizy danych z pliku binarnego zawierającego sygnały w dziedzinie czasu. Program wczytuje dane z pliku, przetwarza je, a następnie zapisuje wyniki do pliku ROOT. Program generuje również histogramy i wykresy 2D, które przedstawiają różne parametry sygnałów, takie jak amplituda, czas nadejścia sygnału (T0), ładunek oraz czas powyżej progu (TOT).

Użycie programu
Program domyślnie wczytuje dane z pliku wave_0.dat. Możesz zmienić nazwę pliku w kodzie źródłowym, jeśli jest to konieczne.

Po uruchomieniu program przetwarza dane i zapisuje wyniki do pliku output.root.

Program generuje następujące histogramy i wykresy 2D:

hT0: Histogram czasu nadejścia sygnału (T0).

hCharge: Histogram ładunku sygnału.

hAmplitude: Histogram amplitudy sygnału.

hTOT: Histogram czasu powyżej progu (TOT).

hTOTVsT0: Wykres 2D przedstawiający zależność TOT od T0.

hAmplitudeVsCharge: Wykres 2D przedstawiający zależność amplitudy od ładunku.

hChargeVsT0: Wykres 2D przedstawiający zależność ładunku od T0.

hChargeVsTOT: Wykres 2D przedstawiający zależność ładunku od TOT.

hAmplitudeVsTOT: Wykres 2D przedstawiający zależność amplitudy od TOT.

Histogramy i wykresy są wyświetlane w oknie graficznym, a następnie zapisywane do pliku histograms.png.

Program kończy działanie po zamknięciu okna graficznego.

Struktura kodu
Klasa MySignal: Klasa przechowująca parametry sygnału, takie jak amplituda, czas nadejścia (T0), ładunek oraz czas powyżej progu (TOT).

Funkcja zadanie2: Główna funkcja programu, która wykonuje całą logikę wczytywania danych, przetwarzania ich, zapisywania wyników do pliku ROOT oraz generowania histogramów i wykresów.

Wczytywanie danych: Program wczytuje dane z pliku binarnego i przetwarza je w pętli.

Obliczanie parametrów sygnału: Dla każdego zdarzenia program oblicza wartość bazową (baseline), amplitudę, czas nadejścia (T0), ładunek oraz czas powyżej progu (TOT).

Zapisywanie wyników: Wyniki są zapisywane do drzewa ROOT w pliku output.root.

Generowanie histogramów: Program generuje histogramy i wykresy 2D na podstawie danych z drzewa ROOT.

Wyświetlanie i zapisywanie wyników: Histogramy i wykresy są wyświetlane w oknie graficznym i zapisywane do pliku histograms.png.

Pliki wyjściowe
output.root: Plik ROOT zawierający drzewo z danymi o sygnałach.

histograms.png: Plik z zapisanymi histogramami i wykresami 2D.
