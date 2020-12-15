import React, { Component } from "react";
import {StyleSheet} from "react-native";
import {BarChart} from "react-native-chart-kit";
import { Dimensions } from "react-native";
import {Block, Text, Button, Linking} from "../components";
import { theme} from "../constants";


const screenWidth = Dimensions.get("window").width;
const chartConfig = {
  backgroundGradientFrom: "#ffffff",
  backgroundGradientTo: "#ffffff",
  color: (opacity = 1) => `rgba(3, 49, 130, ${opacity})`, 
  fillShadowGradientOpacity: 1
};


const data = {
  labels: ["Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"],
  datasets: [
    {
      data: [20, 45, 28, 80, 99, 43, 22],
    }
  ]
};

class Settings extends Component {
  

  dialCall = () => {
    Linking.openURL('tel:${091123456789}'); //preset phone number
  };
  
  render() {
    const { navigation } = this.props;

    return (
      <Block>
        <Block flex={false} row center space="between" style={styles.header}>
          <Text h1 bold>
            Weekly Reports
          </Text>
        </Block>
        
        <BarChart style = {{paddingRight:-10}}
            data={data}
            width={screenWidth}
            height={256}
            showValuesOnTopOfBars={true}
            withHorizontalLabels={false}
            chartConfig={chartConfig}
            verticalLabelRotation={30}
          />  
          <Block>
          <Text center style={{ fontWeight: 'bold' , fontSize: 20 }}> You have used {(data.data) } Units</Text>
          <Text center style={{ fontWeight: 'bold' , fontSize: 20 }}> Cost = {(data.data)} Rs/-</Text>
          <Text center>This chart indicates your consumed electricity in units. </Text>
          <Text center>1 unit = (1000 watts * 1 hour)</Text>
          <Block middle flex={0.5} margin={[100, theme.sizes.padding * 2]}>
          <Button gradient onPress={() => navigation.navigate("Reports")}>
            <Text center bold white>
              Daily Report
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
