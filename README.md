# Tic-Tac-Toe Game using TinyML and BLE

## Authors
[Dinesh Reddy Chinta](https://github.com/chintadinesh)
Tejas Bhagwat 


## Project Overview
The project involves implementing the popular tic-tac-toe game using speech recognition for player inputs and Bluetooth Low Energy (BLE) integration to track the status of the game on a mobile device.
The following points describe the project overview:

  * TinyML for Arduino
  * How to train a model
  * Code overview 
  * Tic-Tac-Toe game 
  * Challenges 
  * Taking input from the user
  * BLE integration
  * Game play demo
  * References

# TinyML for Arduino
  Machine Learning involves training a model on previously collected, processed data, to be able to predict about the new data.
  The tasks vary in various levels of complexity. 
    Examples: image recognition, speech recognition, branch prediction in pipelined CPU design. 
  The training task involves several iterations and epochs. The model incrementally learns several parameters from the data which impacts the output. There are several models in Machine Learning that can learn from data.  
    Examples: Support Vector Machines, Multi Layer Perceptron, Convolutional Neural Network….
  To test the efficacy of the learnt model, we test it on some unseen data. Precision, recall are some of the generally used metrics to test a model. We will be using them in the later sections of this project. The attached image gives a good pictorial representation of the metrics.
Precision: True PositivesTrue Positives + False Positives
Recall: True PositivesTrue Positives + False Negatives

      Fig1. Precision and Recall terms

  A good model has high Precision and Recall scores.
The training can be compute, memory and storage intensive, and can be done in servers to achieve good accuracy scores. In general, the training is performed in floating point precision.
  However, the inference, in the context of Embedded devices, is done on resource constrained devices. We convert all the floating point numbers in the model to fixed point representations. Machine learning models are also tolerant to some degree of noise in the input data. This helps in using computationally efficient fixed point operations for the ML tasks without compromising much on the accuracy of predictions.

## I. How to train a model	
  Training a Machine Learning model requires us to determine the following:
What is the task that the model is trying to fit?

  In our case, we want our model to recognize words, and recognize patterns in the images.
Once the objective of the ML model is determined, we need to know the number of classes the model is trying to predict. To this end, we have 2 words for speech recognition and 10 digits for pattern recognition.
Additionally, one important task in Machine Learning is the data that the model is trained with and data for which the model is used to predict. In our current case, we use the data available in this repository [6]. One advantage of using the data is that it has already been labelled. In the ideal case, the characteristics of the inference data should be the same as those of the train data. In our case, we are using the data from the dataset. However, labeling the data is a tedious task, and hence we usually are satisfied with the representative training data for good repositories.

  In our specific case, we only retrain the speech model. The dataset has a good number of representative tasks for nor tasks. For example, numbers from “zero” to “nine”, “left”, “right” ….

  Currently, micro-speech Arduino project comes with a pre-trained model with words “yes”, “no”. Provided that the model is only effective for two words, we can choose to train the model with “zero”, “one”.

### Jupyter notebook retraining code discussion

  Once we choose the words, change the WANTED\_WORDS, variable in the notebook from “yes,no” to “zero,one”

  The current learning rates are set to run for 2 hours. Since our target is embedded board, we can increase the learning rate and reduce the number of training steps to reduce the training time. This is only possible because our inference is in fixed-point and compromising a little bit on accuracy during training is acceptable.

  Here are some of the parameters that we can play with in the notebook. From our end, we did not modify any of them:

    ```
    QUANT_INPUT_MIN = 0.0
    QUANT_INPUT_MAX = 26.0
    SAMPLE_RATE = 16000
    CLIP_DURATION_MS = 1000
    WINDOW_SIZE_MS = 30.0
    FEATURE_BIN_COUNT = 40
    BACKGROUND_FREQUENCY = 0.8
    BACKGROUND_VOLUME_RANGE = 0.1
    TIME_SHIFT_MS = 100.0
    ```

  As it can be noted in the code, we are using ‘Tiny\_conv’ architecture, which is a low over-head 2-layer ML model suitable for embedded boards. The following diagram displays the architecture:

### Setup and Running
  Though we can run the Jypyter notebook on Google-collab, we would recommend you to set up the environment on your local machine. This is because Google-colab gives a limited run-time on a machine, around 3 hours based on our observations. Once your quota is complete, you will have to run the code on a different machine. This would effectively download the data repository, which is around 500MB, again. We explored the possibility of mounting the repository on Google Drive so that we don’t need to download the repo each time. But this effort wasn’t very successful.

  In the first stage, we train the model in floating point format, test the model on the test data.
The Tensorflow Lite version converts the model from floating point to fixed point version. 
To run this on Micro controllers, we need to run this through another step of converting the fixed point version into ‘C source code’ using ‘xdd’ utility. Once the previous step is run, we can find “micro\_speech/micro\_features/model.cc“ C source code for the model. All we need to do is to copy paste the array into the appropriate Arduino project files. 

  Here are some of our observations on the model sizes based on our experiments:

    Magic wand: 31,256 B
    Micro Speech
    2-word-input model: 18,712 B
    11 word-inputs model: 26,720 B
    Here is a video of us testing for two words, ‘yes’, ‘no’ on the board.

### 2. Tic-Tac-Toe game

#### Game rules
- It is a 3x3 matrix game.
- The first player to get three rows, columns, or diagonal wins the game.
- Starter code for the game: here is the C starter code for the game.
- We adapted the starter code to our requirements.
- For the game design, we follow these steps when we get new input:
- new input should not be taken for already existing position
- The sequence of players should also be maintained.
- eg,. player 1 must enter the input after player 2.
- After the game is over, we should not take any input.
- Let us design a simple state-machine based on the above requirements.
- We need states for the following
- player1 is playing.
- player2 is playing.
- game over.

  We print the board to the serial monitor, when a new entry is made, to track the status of the game.
  Challenges for playing the game on the microcontroller:

  As noted in Lab4, the Recall rate for the speech recognition is very low for the board. 
  Precision = 9/10
  Recall = 3/10

Now, let us analyze the ways in which we can take input from the user:

Like a remote input: \<up/down/left/right, select\>

Like a dial pad: \<number, select/retake\>

Binary Phase Shift Keying protocol

        	1 -> 0b0001
        	2 -> 0b0010
        	3 -> 0b0011
        	4 -> 0b0100
        	5 -> 0b0101
        	6 -> 0b0110
        	7 -> 0b0111
            8 -> 0b1000
        	9 -> 0b1001

  Here we encode our words “yes” to 1 and “no” to 0.

  In the gesture recognition model, we did an unsymmetric mapping of inputs to bits “1”, “0”. This increased the precision recall scores of the model.

  Map digits to 0 or 1

    * "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"
    * "0", "1", "0", "0", "0", "0", "0", "1", "0", "0"

  New metrics:

      Precision = 9/10 
      Recall = 10/10

  To further reduce the error rate, we added two levels of protection for each entry:

  Input is not a single step. This is how input is taken:

  BPSK encoding scheme for taking inputs.
    _ _ _ _ _ _ 

      - Position on the board as first four bits: _ _ _ _
      - The next bit is whether the board has detected the speech correctly.
      - The user can simply disable the current input by setting this bit to 0
      - The last bit is for parity. If this goes wrong, the input is discarded.
      - This last bit is just for an additional layer of conformity.


    Example: 
    0b000110



References

[1] [Jupyter notebook for training your model](https://github.com/tensorflow/tflite-micro/blob/main/tensorflow/lite/micro/examples/micro\_speech/train/train\_micro\_speech\_model.ipynb)

[2] [Micro speech git repository for training your model](https://github.com/tensorflow/tflite-micro/tree/main/tensorflow/lite/micro/examples/micro\_speech/train)

[3] [Starter code for the game in C with number as input](http://www.cprogrammingnotes.com/question/tic-tac-toe-game.html)

[4] [Machine Learning using tinyML](https://docs.google.com/document/d/1VayQr89qMNv3MaO78LifrfpHyxtMV6waWgm95xU0fIM/edit#)

[5] [Speech micro train data](https://storage.googleapis.com/download.tensorflow.org/models/tflite/speech\_micro\_train\_2020\_05\_10.tgz)


