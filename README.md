# Charmed baryons decay widths and mass spectra

Code to compute charmed baryon spectra and decay widths. A fit is performed to obtain the model parameters. Errors are propagated via bootstrap Monte Carlo Gaussian sampling.

## Framework installation

To install the framework you need anaconda and git on a linux machine. In a terminal type:
1. Clone the repository:
  ```
  git clone git@github.com:Ailierrivero/charmed-baryonsFW.git
  ```
2. Access the code:
  ```
  cd charmed-baryonsFW
  ```
3. Install the conda enviroment:
  ```
  conda env create -f config.yml
  conda activate charm-ml
  conda develop .
  ```
3.1 Update the conda enviroment:
   ```
   conda env update --file config.yml --prune
   ```
4. Compile the decay widths C++ code (here we use C++11):
  ```
  cd ./decays/DecayWidths/
  make obj
  make
  cd ../..
  ```
5. Minimal run:
  ```
  python3 ./scripts/bootstrap_three_quark.py
  python3 ./scripts/bootstrap_diquark.py
  python3 ./scripts/print_results.py
  ```
6. Check that your plots and tables are in the newly created directories

7. Edit the ```config/*.json``` to set options according your needs

8. To run batch jobs two systems are supported:

   8.1. HTCondor batch system
   ```
   python3 ./scripts/submit_batch.py three_quark omegas
   ```
   8.2. LSF batch system (Genoa machines)
   ```
   python3 ./scripts/submit_batch_lsf.py three_quark omegas
   ```
