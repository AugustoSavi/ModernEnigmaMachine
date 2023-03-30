import { useState } from 'react'
import {Picker} from '@react-native-picker/picker';
import { StyleSheet, Text, View, TextInput, TouchableOpacity } from 'react-native';

export default function App() {
  const [port, setPort] = useState('/dev/ttyUSB0');
  const [baudRate, setBaudRate] = useState(9600);
  const [mode, setMode] = useState('Normal Keyboard');
  const [text, setText] = useState('');

  const handleConnect = () => {
    // SerialPort.connect(port, baudRate, onDataReceived);
  };

  const handleDisconnect = () => {
    // SerialPort.disconnect();
  };

  const handleSend = () => {
    // const data = Buffer.from(`${mode}\n${text}`);
    // SerialPort.write(data);
  };

  const onDataReceived = (data) => {
    console.log(`Received data: ${data}`);
  };

  return (
    <View style={styles.container}>
      <View style={styles.form}>
        <View style={styles.field}>
          <Text style={styles.label}>Port:</Text>
          <TextInput style={styles.input} value={port} onChangeText={setPort} />
        </View>
        <View style={styles.field}>
          <Text style={styles.label}>Baud Rate:</Text>
          <TextInput style={styles.input} value={baudRate.toString()} onChangeText={setBaudRate} />
        </View>
        <View style={styles.field}>
          <Text style={styles.label}>Mode:</Text>
          <Picker
            selectedValue={mode}
            onValueChange={(itemValue) => setMode(itemValue)}
            style={styles.picker}
            itemStyle={styles.pickerItem}
          >
            <Picker.Item label="Normal Keyboard" value="Normal Keyboard" />
            <Picker.Item label="encrypt" value="encrypt" />
            <Picker.Item label="decrypt" value="decrypt" />
          </Picker>
        </View>
        <View style={styles.field}>
          <Text style={styles.label}>Text:</Text>
          <TextInput style={styles.textarea} value={text} onChangeText={setText} multiline={true} />
        </View>
        <View style={styles.buttons}>
          <TouchableOpacity style={styles.button} onPress={handleConnect}>
            <Text style={styles.buttonText}>Connect</Text>
          </TouchableOpacity>
          <TouchableOpacity style={styles.button} onPress={handleDisconnect}>
            <Text style={styles.buttonText}>Disconnect</Text>
          </TouchableOpacity>
          <TouchableOpacity style={styles.button} onPress={handleSend}>
            <Text style={styles.buttonText}>Send</Text>
          </TouchableOpacity>
        </View>
      </View>
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#f5f5f5',
    alignItems: 'center',
    justifyContent: 'center',
  },
  form: {
    width: '100%',
    height: '100%',
    marginTop: '25%',
    backgroundColor: '#fff',
    padding: 20,
    borderRadius: 5,
    shadowColor: '#000',
    shadowOffset: {
      width: 0,
      height: 1,
    },
    shadowOpacity: 0.22,
    shadowRadius: 2.22,
    elevation: 3,
  },
  field: {
    flexDirection: 'row',
    alignItems: 'center',
    marginBottom: 10,
  },
  label: {
    width: 100,
    marginRight: 10,
    fontSize: 16,
    fontWeight: 'bold',
  },
  input: {
    flex: 1,
    borderWidth: 1,
    borderColor: '#ccc',
    borderRadius: 5,
    padding: 10,
    fontSize: 16,
  },
  textarea: {
    borderWidth: 1,
    borderColor: '#ccc',
    borderRadius: 5,
    padding: 10,
    fontSize: 16,
    height: 123,
    width: '70%'
  },
  buttons: {
    flexDirection: 'row',
    justifyContent: 'space-between',
    marginTop: 20,
  },
  button: {
    backgroundColor: '#007aff',
    padding: 10,
    borderRadius: 5,
    width: '30%',
    alignItems: 'center',
  },
  buttonText: {
    color: '#fff',
    fontSize: 16,
    fontWeight: 'bold',
  },

  picker: {
    backgroundColor: '#ccc',
    borderRadius: 5,
    borderWidth: 3,
    height: 40,
    width: '70%',
    marginBottom: 10,
  },
  pickerItem: {
    color: 'black',
    fontSize: 18,
  }
});

