import React, { Component } from "react";
import {StyleSheet, Picker, Image,View} from "react-native";
import {Button,Block, Text,Switch} from "../components";
import { theme} from "../constants";

class Settings extends Component {
 
  state = {
    selectedValue: null,
    data: [
        "Javascript",
        "Go",
        "Java",
        "Kotlin",
        "C++",
        "C#",
        "PHP"
    ]
};

  render() {
    const { navigation } = this.props;

    return (
      <Block>
        <Block flex={false} row center space="between" style={styles.header}>
          <Text h1 bold>
            Settings
          </Text>
        </Block>
        <Block style={styles.buton}> 
        <Block row center space ="between" style={{flex:0.5}}>
              <Text gray2>Notifications</Text>
              <Switch
                value={this.state.notifications}
                onValueChange={value => this.setState({ notifications: value })}
              />
          </Block> 
          <View style ={{alignItems: 'center'}}>
            <Image source={require("../assets/images/Meter.png")} />
          </View>
              <Picker>
                <Picker.Item label = "Meter 1" value = "1" />
                <Picker.Item label = "Meter 2" value = "2" />
                <Picker.Item label = "Meter 3" value = "3" />
                <Picker.Item label = "Meter 4" value = "4" />
              </Picker>
              <Button gradient onPress={() => navigation.navigate("addMeter")}>     
                <Text bold white center>
                  Add New Meter
                </Text>
              </Button>
              <Button RedGradient onPress={() => navigation.navigate("Forgot")}>     
                <Text bold white center>
                  Delete Meter
                </Text>
              </Button>
          </Block>
          
      </Block>
    );
  }
}



export default Settings;

const styles = StyleSheet.create({
  header: {
    paddingHorizontal: theme.sizes.base * 2
  },
  buton: {
    paddingHorizontal: theme.sizes.base * 2,
     
  }
});
