import std;
import ui;

int main(){
  try {
    App app(
      AppSetting{
        .title = "MyApp",
        .verbose = true
      });
    app.run();
  } catch (AppError err) {
    std::println("{}", err.what());
    // std::println("{}", err.stack());
  }
}
