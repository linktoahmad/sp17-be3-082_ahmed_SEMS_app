import React, { Component } from "react";
import {StyleSheet} from "react-native";
import {LineChart} from "react-native-chart-kit";
import { Dimensions } from "react-native";
import {Block, Text, Button, Linking} from "../components";
import { theme} from "../constants";


const screenWidth = Dimensions.get("window").width;

const chartConfig = {
  backgroundGradientFrom: "#ffffff",
  backgroundGradientTo: "#ffffff",
  color: (opacity = 1) => `rgba(3, 49, 130, ${opacity})`, 
};

const data = {
  labels: ["1am", "2", "4", "6","8", "10","12", "1pm", "2", "4", "6","8", "10","12pm"],
  datasets: [
    {
      data: [6,8,6,2,5,9,0,7,9,3,3,6,2,5,9,0,7,9,3,3,1,6,9,4]
    }
  ],
 
};

class Settings extends Component {
  state = {
    notifications: true,
  };

  dialCall = () => {
    Linking.openURL('tel:${091123456789}'); //preset phone number
  };
  
  render() {
    const { navigation } = this.props;

    return (
      <Block>
        <Block flex={false} row center space="between" style={styles.header}>
          <Text h1 bold>
            Todays Reports
          </Text>
        </Block>
        <Block top middle>
        <LineChart
          data={data}
          width={screenWidth}
          height={256}
          verticalLabelRotation={30}
          chartConfig={chartConfig}
          bezier
        />
          <Text center style={{ fontWeight: 'bold' , fontSize: 20 }}> You have used {(data.data) } Units</Text>
          <Text center style={{ fontWeight: 'bold' , fontSize: 20 }}> Cost = {(data.data)} Rs/-</Text>
          <Text center>This chart indicates your consumed electricity in units. </Text>
          <Text center>1 unit = (1000 watts * 1 hour)</Text>
          <Block middle flex={0.5} margin={[100, theme.sizes.padding * 2]}>
          <Button gradient onPress={() => navigation.navigate("WeekReports")}>
            <Text center bold white>
              Weekly Report
            </Text>
          </Button>
          <Button gradient onPress={() => navigation.navigate("MonthReports")}>
            <Text center bold white>
              Monthly Report
            </Text>
          </Button>
        </Block>
        </Block>
      </Block>
    );
  }
}



export default Settings;

const styles = StyleSheet.create({
  header: {
    paddingHorizontal: theme.sizes.base * 2
  }
});