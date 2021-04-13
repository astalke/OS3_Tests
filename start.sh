#!/usr/pkg/bin/bash

echo -n "W testach badających poprawne zabijanie procesu pojawia sie smieci"
echo -n " w terminalu. Skrypt sie zatrzyma na niepoprawnym tescie i wypisze"
echo " komunikat o bladzie - nie przejmowac sie dopoki sie nie zatrzyma."
echo "Uwaga! Testy pewnie wygeneruja troche plikow core.*"
echo "No i oczywiscie skrypt po sobie nie sprzata :p"

# Kompilacja wszystkich plikow w tests.txt
# sed jest do pomojania wierszy z kodem bledu
for f in $(sed -e n\;d<tests.txt); do
  if ! clang -O2 -o $f $f.c; then
    echo "COMPILE FAILURE"
    exit 1
  fi
done


# Petla iterujaca sie po danych z tests.txt
while read f; do
  read t
  echo -n "$f: "
  if [[ $t == "0" ]]; then
    if ./$f; then
      echo "OK"
    else
      echo "FAIL"
      exit 1
    fi
  else
    if ./$f; then
      echo "FAIL"
      exit 1
    else
      echo "OK"
    fi
  fi  
done < tests.txt

# Cytujac tresc:
# gdy zostanie wywolana z parametrem roznym od zera, powoduje, że gdy proces 
# wywolujacy te funkcje zakonczy dzialanie z kodem zero, rodzic odczyta kod 
# powrotu ROWNY jeden
# Test specjalny, sprawdzajacy czy kod wynikowy jest rowny 1, a nie niezerowy.
if ! clang -O2 -o special special.c; then
  echo "COMPILE FAILURE"
  exit 1
fi
./special
if [[ $? -eq 1 ]]; then
  echo "Special: OK";
else
  echo "Special: FAILED"
  exit 1
fi

if ! clang -O2 -o special2 special2.c; then
  echo "COMPILE FAILURE"
  exit 1
fi
./special2
if [[ $? -eq 2 ]]; then
  echo "Special2: OK";
else
  echo "Special2: FAILED"
  exit 1
fi



echo "Everything is OK!"
