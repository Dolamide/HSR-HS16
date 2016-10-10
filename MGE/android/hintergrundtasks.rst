Hintergrundtasks
================

Problem: Lang laufende Tasks blockieren den UI-Thread (bsp. Download).
Der Main/UI-Thread koordiniert Events, zeichnet GUI (Event-Loop - siehe Grundlagen)

.. code-block:: java

    public void onClick(View v) {

    Runnable runnable = new Runnable() {
       @Override
       public void run() {
           // Hier kann nicht auf UI zugegriffen werden!
           final Bitmap bitmap = download("http://slow.hsr.ch/hsr_cat.bmp");

           // command wird im UI-Thread ausgeführt
           Runnable command = new Runnable() {
               @Override
               public void run() {
                   imageView.setImageBitmap(bitmap);
               }
           };
           imageView.post(command);
       }
    };
    Thread thread = new Thread(runnable);
    thread.start();
    }

AsyncTask
----------
Schönere Variante als oben!

.. code:: java

    class DownloadBitmapTask extends AsyncTask<String, Integer, Bitmap> {
        @Override
        protected void onPreExecute() {
            // Wird im UI-Thread ausgeführt
            super.onPreExecute();
        }
        @Override
        protected Bitmap doInBackground(String... params) {
            // Background Task
            publishProgress(10);
            return download(params[0]);
        }
        @Override
        protected void onPostExecute(Bitmap bitmap) {
            // Wird im UI-Thread ausgeführt
            imageView.setImageBitmap(bitmap);
        }
        @Override
        protected void onProgressUpdate(Integer... values) {
            // Wird im UI-Thread ausgeführt
           progressBar.setProgress(values[0]);
        }
    }

    new DownloadBitmapTask().execute("http://slow.hsr.ch/hsr_cat.bmp");
