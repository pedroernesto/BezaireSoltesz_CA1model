# BezaireSoltesz_CA1model

A SciUnit package for data-driven testing of Hippocampus microcircuit models

<div><img src="https://raw.githubusercontent.com/appukuttan-shailesh/morphounit/master/eu_logo.jpg" alt="EU Logo" width="15%" align="right"></div>

### ACKNOWLEDGEMENTS
The work has been supported in part or in whole in the Human Brain Project, funded from European Union Horizon 2020 Framework Programme for Research and Innovation, Grant Agreements No. 785907 and No. 945539 (Human Brain Project SGA2 and SGA3)

# Description
This forked repository contains validation tests for a microcircuit model of CA1 region [1], that are built on the base of experimental data [2,3].

[1] Bezaire MJ, Raikov I, Burk K, Vyas D and Soltesz I (2016). Interneuronal mechanisms of hippocampal theta oscillations in a full-scale model of the rodent CA1 circuit, eLife 5: e18566, 10.7554/eLife.18566

[2] Bezaire MJ, Soltesz I. 2013. Quantitative Assessment of CA1 Local Circuits: Knowledge Base for Interneuron-Pyramidal Cell Connectivity. Hippocampus:23(9) 751-785.

[3] Sasaki T, Kimura R, Tsukamoto M, Matsuki N and Ikegaya Y (2006). Integrative spike dynamics of rat CA1 neurons: a multineuronal imaging study. The Journal of Physiology 574 (1): 195-208, 10.1113/jphysiol.2006.108480

# Dependencies
- NEURON simulator

# Qualitattive validation tests for Sasaki et al. (2006) experiment:

<div>
  <img src="https://github.com/pedroernesto/BezaireSoltesz_CA1model/blob/main/Scale_100_SpikesTrainSingleSpike_SimDuration_20_all_rasters.gif" alt="Example1" width="100%">
  <img src="https://github.com/pedroernesto/BezaireSoltesz_CA1model/blob/main/Scale_100_SpikesTrainSingleSpike_SimDuration_20_all_slices.gif" alt="Example2" width="100%">
  <img src="https://github.com/pedroernesto/BezaireSoltesz_CA1model/blob/main/Scale_100_SpikesTrainSingleSpike_SimDuration_20_all_pyramidalcell.gif" alt="Example3" width="100%">
  <img src="https://github.com/pedroernesto/BezaireSoltesz_CA1model/blob/main/Scale_100_SpikesTrainSingleSpike_SimDuration_20_CA3_pyramidalcell.png" alt="Example4" width="100%">
</div>

