A package for data-driven testing of Hippocampus microcircuit models

<div><img src="https://raw.githubusercontent.com/appukuttan-shailesh/morphounit/master/eu_logo.jpg" alt="EU Logo" width="15%" align="right"></div>

### ACKNOWLEDGEMENTS
Dr. Ivan Raikov provided useful comments on the Bezaire et al. (2016) model during the progress of this study. In addition, Dr Julian M. Budd at HBP Hippocampus team suggested the Sasaki et al. (2006) experimental work for validation tests.

This work has been supported in part or in whole in the Human Brain Project, funded from European Union Horizon 2020 Framework Programme for Research and Innovation, Grant Agreements No. 785907 and No. 945539 (Human Brain Project SGA2 and SGA3)

# Description
This repository contains slicing functionalities and (qualitative) validation tests for a detailed NEURON simulator-based microcircuit model for the rat Hippocampus CA1 region [1]. The model is based on reported experimental data [2]. Currently, this repository contains qualitative tests of Bezaire et al. (2016) model against Sasaki et al. (2006) experimental data [3]. Preliminary results have been presented at Bernstein Conference for Computationl Neuroscience (2022) [4].

[1] Bezaire MJ, Raikov I, Burk K, Vyas D and Soltesz I (2016). Interneuronal mechanisms of hippocampal theta oscillations in a full-scale model of the rodent CA1 circuit, eLife 5: e18566, 10.7554/eLife.18566. Source code available at ModelDB: http://modeldb.science/showmodel?model=187604

[2] Bezaire MJ, Soltesz I. 2013. Quantitative Assessment of CA1 Local Circuits: Knowledge Base for Interneuron-Pyramidal Cell Connectivity. Hippocampus:23(9) 751-785.

[3] Sasaki T, Kimura R, Tsukamoto M, Matsuki N and Ikegaya Y (2006). Integrative spike dynamics of rat CA1 neurons: a multineuronal imaging study. The Journal of Physiology 574 (1): 195-208, 10.1113/jphysiol.2006.108480

[4] García-Rodríguez P., Pananceau M., Davison A. P. (2022) Quasi-linear I-O activation transfer of CA3-CA1 projections, in a detailed biophysical model for Hippocampus CA1. Bernstein Conference 2022. https://abstracts.g-node.org/conference/BC22/abstracts#/uuid/d5f01881-d692-4a9c-8ebc-6001434c6860

# Dependencies
- NEURON simulator

# Qualitative validation tests following Sasaki et al. (2006) experiment

<div>
  <img src="https://github.com/pedroernesto/BezaireSoltesz_CA1model/blob/main/Scale_100_SpikesTrainSingleSpike_SimDuration_20_all_rasters.gif" alt="Example1" width="100%">
  <img src="https://github.com/pedroernesto/BezaireSoltesz_CA1model/blob/main/Scale_100_SpikesTrainSingleSpike_SimDuration_20_all_slices.gif" alt="Example2" width="100%">
  <img src="https://github.com/pedroernesto/BezaireSoltesz_CA1model/blob/main/Scale_100_SpikesTrainSingleSpike_SimDuration_20_all_pyramidalcell.gif" alt="Example3" width="100%">
  <img src="https://github.com/pedroernesto/BezaireSoltesz_CA1model/blob/main/Scale_100_SpikesTrainSingleSpike_SimDuration_20_CA3_pyramidalcell.png" alt="Example4" width="100%">
</div>

