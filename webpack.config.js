const path = require("path");
const { ModuleFederationPlugin } = require("webpack").container;
const pkg = require("./package.json");

module.exports = (env = {}) => ({
  name: pkg.config.shortname,
  mode: "production",
  cache: false,
  devtool: "source-map",
  optimization: {
    minimize: false,
  },
  target: "web",
  entry: path.resolve(__dirname, "./src/index.js"),
  output: {
    publicPath: !env.prod ? "http://localhost:3002/" : pkg.config.publicPath,
  },
  resolve: {
    extensions: [".vue", ".jsx", ".js", ".json"],
  },
  module: {
    rules: [
      {
        test: /\.(png|jpg|gif)$/i,
        use: [
          {
            loader: "url-loader",
            options: {
              limit: 8192,
            },
          },
        ],
      },
    ],
  },
  plugins: [
    new ModuleFederationPlugin({
      name: pkg.config.shortname,
      library: { type: "amd", name: pkg.config.shortname },
      filename: "remoteEntry.js",
      remotes: {
        "lenna-web": "lenna-web",
      },
      exposes: {
        default: "./src/",
      },
      remotes: {},
      shared: [],
    }),
  ],
  experiments: {
    syncWebAssembly: true,
  },
  devServer: {
    contentBase: path.join(__dirname),
    compress: true,
    port: 3002,
    hot: true,
    headers: {
      "Access-Control-Allow-Origin": "*",
      "Access-Control-Allow-Methods": "GET, POST, PUT, DELETE, PATCH, OPTIONS",
      "Access-Control-Allow-Headers":
        "X-Requested-With, content-type, Authorization",
    },
  },
});
