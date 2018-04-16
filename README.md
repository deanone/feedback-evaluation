This is the sophisticated version of the SocialCar feedback-evaluation module.

The overall system consists of 2 distinct modules:
- The travel preferences clustering module
- The reputation calculation module

The source code of the 2 modules is placed in the corresponding directory, along with the `rapidjson` library and supplementary bash scripts.

As this new version includes the rapidjson library, the only required library is the following:
- [cURL](https://curl.haxx.se/libcurl/)

The 2 generated executables along with the corresponding properties files should be placed **IN THE SAME DIRECTORY**.

The `clustering` module runs periodically (every day) as cronjob and generates clusters of users based on their travel preferences.

The `reputation` calculation module runs periodically (every hour) as cronjob and updates the reputation scores of the users based on the generated clusters and the incoming feedbacks. 
