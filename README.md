# 2023_Autonomous_system_platform_final_project

Repository for Konkuk univ. Smart Vehicle Engineering. 2023 Autonomous system platform final project

</br>

# 1. Installation

## 1) Clone repository

### a. Using CLI

```bash
 git clone https://github.com/Konkuk-AILab/2022-Autonomous-system-platform-final.git
```

### b. Using github-desktop
- Install github desktop (GUI)
```bash
 sudo wget https://github.com/shiftkey/desktop/releases/download/release-3.1.1-linux1/GitHubDesktop-linux-3.1.1-linux1.deb
 ### Uncomment below line if you have not installed gdebi-core before
 # sudo apt-get install gdebi-core 
 sudo gdebi GitHubDesktop-linux-3.1.1-linux1.deb
```
</br>

## 2) Install dependent pacakges
```bash
 sudo apt-get update
 sudo apt-get install ros-noetic-jsk-rviz-plugins # For visualization
 pip install pygame
```
</br>

# 2. Launch simulator
```bash
 # Build package
 cd ~/2022-Autonomous-system-platform-final
 catkin_make
 
 # Allow permission
 sudo chmod +x src/shellScripts/launch.sh
 sudo chmod +x src/final_project/final_autonomous_driving/scripts/simultaneous_inputs.py
 
 # Launch sim
 sh src/shellScripts/launch.sh
```
</br>

# 3. Modify source code
- Modify source code with your favorite text editor
- You can modify following files
    - `src/final_project/final_autonomous_driving/src/autonomous_driving.cpp`
- If you want to disable manual control
    - Go to `src/final_project/final_simulator/launch/simulation.launch`
    - Set argument "use_manual_inputs" into false

</br>

Good Luck!